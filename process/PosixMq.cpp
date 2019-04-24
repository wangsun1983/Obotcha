#include <stdio.h>
#include <string.h>     //for strerror()
#include <errno.h>

#include "PosixMq.hpp"

namespace obotcha {

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
    String sp = "/";
    mQName = sp->append(name);
    mType = type;
    mMsgSize = msgsize;
    mMaxMsgs = maxmsgs;
}

bool _PosixMq::init() {
    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = 10;
    mqAttr.mq_msgsize = 1024;

    mQid = mq_open(mQName->toChars(), O_RDWR|O_CREAT, S_IWUSR|S_IRUSR, &mqAttr);
    if (mQid < 0) {
        if (errno == EEXIST) {
            mQid = mq_open(mQName->toChars(), O_RDWR);
        }
    }

    //mq_attr mqAttr;
    //mq_getattr(mQid, &mqAttr);
    //printf("msg size is %d \n",mqAttr.mq_msgsize);


    printf("init fd is %d \n",mQid);
    return (mQid > 0);
}

bool _PosixMq::send(ByteArray data,int prio) {
    if(mType == RecvMq) {
        return false;
    }
    printf("mq_send start send mQid is %d\n",mQid);
    int result = mq_send(mQid, data->toValue(), data->size(), prio);
    if(result == -1) {
        printf("mq_send errno: %s \n",strerror(errno));
    }
    return (result != -1);
}

bool _PosixMq::send(ByteArray data) {
    return send(data,1);
}

int _PosixMq::receive(ByteArray buff) {
    if(mType == SendMq) {
        return false;
    }

    unsigned int prio;

    mq_attr mqAttr;
    mq_getattr(mQid, &mqAttr);

    printf("recve buff size is %d,mqAttr.mq_msgsize is %ld mQid is %d \n",buff->size(),mqAttr.mq_msgsize,mQid);
    int result = mq_receive(mQid, buff->toValue(),buff->size(), NULL);

    if(result == -1) {
        printf("mq_recv errno: %s \n",strerror(errno));
    }

    return result;

}

_PosixMq::~_PosixMq() {
    //mq_close(mQid);
    //mq_unlink(mQName->toChars());
}

}
