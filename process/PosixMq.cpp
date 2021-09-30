#include <stdio.h>
#include <string.h>     //for strerror()
#include <errno.h>
#include <limits.h>

#include "FileInputStream.hpp"
#include "PosixMq.hpp"
#include "System.hpp"
#include "Error.hpp"

namespace obotcha {

int _PosixMq::MAX_MSG_NUMS = -1;
int _PosixMq::MAX_MSG_SIZE = -1;

_PosixMq::_PosixMq(String name,int type) {
    initParam(name,type,DEFAULT_MQ_MSG_SIZE,DEFAULT_MQ_MSG_NUMS);
}

_PosixMq::_PosixMq(String name,int type,int msgsize) {
    initParam(name,type,msgsize,DEFAULT_MQ_MSG_NUMS);
}
    
_PosixMq::_PosixMq(String name,int type,int msgsize,int maxmsgs) {
    initParam(name,type,msgsize,maxmsgs);
}

void _PosixMq::initParam(String name,int type,int msgsize,int maxmsgs) {
    String sp = createString("/");
    mQName = sp->append(name);
    mType = type;
    mMsgSize = msgsize;
    mMaxMsgs = maxmsgs;
}

int _PosixMq::init() {
    ByteArray readBuff = createByteArray(32);
    if(MAX_MSG_NUMS == -1) {
        FileInputStream reader = createFileInputStream("/proc/sys/fs/mqueue/msg_max");
        reader->read(readBuff); 
        MAX_MSG_NUMS = readBuff->toString()->toBasicInt();
    }

    if(MAX_MSG_SIZE == -1) {
        FileInputStream reader = createFileInputStream("/proc/sys/fs/mqueue/msgsize_max");
        readBuff->clear();
        reader->read(readBuff);

        MAX_MSG_SIZE = readBuff->toString()->toBasicInt();
    }

    if(mMaxMsgs > MAX_MSG_NUMS) {
        return -OverSize;
    }

    if(mMsgSize > MAX_MSG_SIZE) {
        return -OverSize;
    }

    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = mMaxMsgs;
    mqAttr.mq_msgsize = mMsgSize;

    mQid = mq_open(mQName->toChars(), O_RDWR|O_CREAT, S_IWUSR|S_IRUSR, &mqAttr);
    if (mQid < 0) {
        if (errno == EEXIST) {
            mQid = mq_open(mQName->toChars(), O_RDWR);
        }
    }

    mq_getattr(mQid, &mqAttr);
    if(mqAttr.mq_maxmsg != mMaxMsgs) {
        close(mQid);
        mQid = -1;
        return -AttributeSetFail;
    }

    if(mqAttr.mq_msgsize != mMsgSize) {
        close(mQid);
        mQid = -1;
        return -AttributeSetFail;
    }

    return mQid;
}

int _PosixMq::send(ByteArray data,PosixMqPriority prio) {
    if(mType == RecvMq) {
        return -InvalidParam;
    }

    if(mQid == -1) {
        return -NotCreate;
    }

    if(data->size() > mMsgSize) {
        return -OverSize;
    }

    return mq_send(mQid, (char *)data->toValue(), data->size(), prio);
}

int _PosixMq::send(ByteArray data) {
    return send(data,PosixMqPriortyLow);
}

int _PosixMq::receive(ByteArray buff) {
    if(mType == SendMq) {
        return -InvalidParam;
    }

    unsigned int priority = 0;
    return mq_receive(mQid, (char *)buff->toValue(),mMsgSize, &priority);;
}

int _PosixMq::sendTimeout(ByteArray data,PosixMqPriority prio,long timeInterval) {
    if(mType == SendMq) {
        return -InvalidParam;
    }

    if(mQid == -1) {
        return -NotCreate;
    }

    if(data->size() > mMsgSize) {
        return -OverSize;
    }


    struct timespec ts;
    /* 
    clock_gettime(CLOCK_REALTIME, &ts);
    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;
    
    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);*/
    st(System)::getNextTime(timeInterval,&ts);

    return mq_timedsend(mQid, (char *)data->toValue(), data->size(), prio,&ts);;
}

int _PosixMq::sendTimeout(ByteArray data,long waittime) {
    return sendTimeout(data,PosixMqPriortyLow,waittime);
}

int _PosixMq::receiveTimeout(ByteArray buff,long timeInterval) {
    if(mType == SendMq) {
        return -InvalidParam;
    }

    struct timespec ts;
    /*
    clock_gettime(CLOCK_REALTIME, &ts);
    long secs = timeInterval/1000;
    timeInterval = timeInterval%1000;
    
    long add = 0;
    timeInterval = timeInterval*1000*1000 + ts.tv_nsec;
    add = timeInterval / (1000*1000*1000);
    ts.tv_sec += (add + secs);
    ts.tv_nsec = timeInterval%(1000*1000*1000);
    */
    st(System)::getNextTime(timeInterval,&ts);
    unsigned int priority = 0;

    return mq_timedreceive(mQid, (char *)buff->toValue(),mMsgSize, &priority,&ts);
}

_PosixMq::~_PosixMq() {
    mq_close(mQid);
}

void _PosixMq::clean() {
    mq_unlink(mQName->toChars());
}

void _PosixMq::release() {
    mq_close(mQid);
}

void _PosixMq::destroy() {
    mq_close(mQid);
    mq_unlink(mQName->toChars());
}

}
