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

DECLARE_SIMPLE_CLASS(PosixMq) {
public:
    _PosixMq(String,int);

    bool init();

    bool send(ByteArray data,int prio);

    bool send(ByteArray data);

    int receive(ByteArray buff);

    ~_PosixMq();

private:

    mqd_t mQid;

    bool isCreated;

    String mQName;

    int mType;
   
};

}
#endif
