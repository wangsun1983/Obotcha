#ifndef __OBOTCHA_POSIX_MQ_HPP__
#define __OBOTCHA_POSIX_MQ_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <signal.h>
#include <fstream>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"

namespace obotcha {

/*
 * only point to point.
 * can not 1 to 2(3,4....)
 */

DECLARE_CLASS(PosixMqListener) {
public:
    virtual void onData(ByteArray) = 0;
};

using _PosixMqLambda = std::function<void(ByteArray)>;
DECLARE_CLASS(PosixMqListenerLambda) IMPLEMENTS(PosixMqListener) {
public:
    _PosixMqListenerLambda(_PosixMqLambda f);
    
    void onData(ByteArray data);

private:
    _PosixMqLambda func;
};

DECLARE_CLASS(PosixMq) {
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
    
    _PosixMq(String name,int type,int msgsize = 1024,int maxmsgs = 8);

    _PosixMq(String name,PosixMqListener listener,int msgsize = 1024,int maxmsgs = 8);
    
    _PosixMq(String name,_PosixMqLambda,int msgsize = 1024,int maxmsgs = 8);

    int init();

    void close();

    void clear();

    int send(ByteArray data,Priority prio);

    int send(ByteArray data);

    int receive(ByteArray buff);

    int sendTimeout(ByteArray data,long waittime,Priority prio = Priority::Low);

    int receiveTimeout(ByteArray buff,long waittime);

    int getMsgSize();

    ~_PosixMq();

private:
    static Mutex mMutex;
    static PosixMq Mq;
    static void onSigUsr1(int signo);

    int getSystemMqAttr(String);

    mqd_t mQid;

    bool isCreated;

    String mQName;

    int mType;

    int mMsgSize;

    int mMaxMsgs;

    struct sigevent sigev;
    PosixMqListener mqListener;

    static int MaxMsgNums;

    static int MaxMsgSize;
};

}
#endif
