#ifndef __OBOTCHA_PROCESS_MQ_HPP__
#define __OBOTCHA_PROCESS_MQ_HPP__

#include <mqueue.h>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "Mutex.hpp"

namespace obotcha {
/*
 * only point to point.
 * can not 1 to 2(3,4....)
 */

DECLARE_CLASS(ProcessMqListener) {
public:
    virtual void onData(ByteArray) = 0;
};

using _ProcessMqLambda = std::function<void(ByteArray)>;
DECLARE_CLASS(ProcessMqListenerLambda) IMPLEMENTS(ProcessMqListener) {
public:
    _ProcessMqListenerLambda(_ProcessMqLambda f);
    
    void onData(ByteArray data);

private:
    _ProcessMqLambda func;
};

DECLARE_CLASS(ProcessMq) {
public:
    enum Type {
        Send = 0,
        Recv,
        AsyncSend,
        AsyncRecv,
    };

    enum Priority {
        Low = 0,
        Normal,
        High,
        Urgent
    };
    
    _ProcessMq(String name,int type,int msgsize = 1024,int maxmsgs = 8);

    _ProcessMq(String name,ProcessMqListener listener,int msgsize = 1024,int maxmsgs = 8);
    
    _ProcessMq(String name,_ProcessMqLambda,int msgsize = 1024,int maxmsgs = 8);

    int init();

    void close();

    void clear();

    int send(ByteArray data,Priority prio);

    int send(ByteArray data);

    int receive(ByteArray buff);

    int sendTimeout(ByteArray data,long waittime,Priority prio = Priority::Low);

    int receiveTimeout(ByteArray buff,long waittime);

    int getMsgSize();

    ~_ProcessMq();

private:
    static Mutex mMutex;
    static ProcessMq Mq;
    static void onSigUsr1(int signo);

    int getSystemMqAttr(String);

    mqd_t mQid;

    bool isCreated;

    String mQName;

    int mType;

    int mMsgSize;

    int mMaxMsgs;

    struct sigevent sigev;
    ProcessMqListener mqListener;

    static int MaxMsgNums;

    static int MaxMsgSize;
};

}
#endif
