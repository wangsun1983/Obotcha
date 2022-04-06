#ifndef __OBOTCHA_POSIX_MQ_HPP__
#define __OBOTCHA_POSIX_MQ_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <mqueue.h>
#include <fstream>


#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArray.hpp"
#include "ArrayList.hpp"

namespace obotcha {

/*
 * only point to point.can not 1 to 2(3,4....)
 */

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

    int init();

    void close();

    void clear();

    int send(ByteArray data,Priority prio);

    int send(ByteArray data);

    int receive(ByteArray buff);

    int sendTimeout(ByteArray data,long waittime,Priority prio = Priority::Low);

    int receiveTimeout(ByteArray buff,long waittime);

    int getMsgSize();

    void notifyAll();

    ~_PosixMq();

private:
    int getSystemMqAttr(String);

    mqd_t mQid;

    bool isCreated;

    String mQName;

    int mType;

    int mMsgSize;

    int mMaxMsgs;

    static int MaxMsgNums;

    static int MaxMsgSize;
};

}
#endif
