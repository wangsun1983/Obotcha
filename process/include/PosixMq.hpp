#ifndef __POSIX_MQ_HPP__
#define __POSIX_MQ_HPP__

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
    PosixMqPriortyLow,
    PosixMqPriortyNormal,
    PosixMqPriortyHigh,
    PosixMqPriortyUrgent
};

enum PosixMqFailReason {
    PosixMqMsgSizeOversize = 200,
    PosixMqNumsOversize,
};

#define DEFAULT_MQ_MSG_SIZE 1024*4
#define DEFAULT_MQ_MSG_NUMS 8

DECLARE_SIMPLE_CLASS(PosixMq) {
public:
    _PosixMq(String name,int type);

    _PosixMq(String name,int type,int msgsize);

    _PosixMq(String name,int type,int msgsize,int maxmsgs);

    int init();

    bool send(ByteArray data,int prio);

    bool send(ByteArray data);

    int receive(ByteArray buff);

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
