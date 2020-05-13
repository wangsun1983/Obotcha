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

enum PosixMqType {
    SendMq = 0,
    RecvMq
};

enum PosixMqPriority {
    PosixMqPriortyLow = 0,
    PosixMqPriortyNormal,
    PosixMqPriortyHigh,
    PosixMqPriortyUrgent
};

#define DEFAULT_MQ_MSG_SIZE 1024*4
#define DEFAULT_MQ_MSG_NUMS 8

DECLARE_SIMPLE_CLASS(PosixMq) {
public:
    _PosixMq(String name,int type);

    _PosixMq(String name,int type,int msgsize);

    _PosixMq(String name,int type,int msgsize,int maxmsgs);

    int init();

    void release();

    void destroy();

    void clean();

    int send(ByteArray data,PosixMqPriority prio);

    int send(ByteArray data);

    int receive(ByteArray buff);

    int sendTimeout(ByteArray data,PosixMqPriority prio,long waittime);

    int sendTimeout(ByteArray data,long waittime);

    int receiveTimeout(ByteArray buff,long waittime);

    ~_PosixMq();

private:

    void initParam(String name,int type,int msgsize,int maxmsgs);

    mqd_t mQid;

    bool isCreated;

    String mQName;

    int mType;

    int mMsgSize;

    int mMaxMsgs;

    static int MAX_MSG_NUMS;

    static int MAX_MSG_SIZE;
};

}
#endif
