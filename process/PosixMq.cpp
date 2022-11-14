#include <mutex>
#include <mqueue.h>
#include <signal.h>

#include "PosixMq.hpp"
#include "System.hpp"
#include "InitializeException.hpp"
#include "FileInputStream.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

namespace obotcha {

//PosixMqListenerLambda
_PosixMqListenerLambda::_PosixMqListenerLambda(_PosixMqLambda f) {
    func = f;
}

void _PosixMqListenerLambda::onData(ByteArray data) {
    func(data);
}

//PosixMq
int _PosixMq::MaxMsgNums = -1;
int _PosixMq::MaxMsgSize = -1;

Mutex _PosixMq::mMutex = createMutex();
PosixMq _PosixMq::Mq = nullptr;

_PosixMq::_PosixMq(String name,int type,int msgsize,int maxmsgs) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        MaxMsgNums = getSystemMqAttr("/proc/sys/fs/mqueue/msg_max");
        MaxMsgSize = getSystemMqAttr("/proc/sys/fs/mqueue/msgsize_max");
    });

    if(maxmsgs > MaxMsgNums || msgsize > MaxMsgSize) {
        Trigger(InitializeException,"invald param");
    }

    if(name->startsWith("/")) {
        mQName = name;
    } else {
        mQName = createString("/")->append(name);
    }
    
    mMaxMsgs = maxmsgs;
    mMsgSize = msgsize;

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
    if(mqAttr.mq_maxmsg != mMaxMsgs || mqAttr.mq_msgsize != mMsgSize) {
        ::close(mQid);
        mQid = -1;
        Trigger(InitializeException,"open msg queue failed");
    }
}

_PosixMq::_PosixMq(String name,PosixMqListener listener,int msgsize,int maxmsgs)
            :_PosixMq(name,AsyncRecv,msgsize,maxmsgs) {
    AutoLock l(mMutex);
    mqListener = listener;
    if(Mq != nullptr) {
        LOG(ERROR)<<"Async Mq["<<name->toChars()<<"] already registed";
        //Trigger(InitializeException,"fail to regist Mq");
    }
    ::signal(SIGUSR1,onSigUsr1);
    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGUSR1;
    Mq = AutoClone(this);
    mq_notify(mQid,&sigev);
}

_PosixMq::_PosixMq(String name,_PosixMqLambda l,int msgsize,int maxmsgs):_PosixMq(name,createPosixMqListenerLambda(l),msgsize,maxmsgs) {
    
}

int _PosixMq::send(ByteArray data,Priority prio) {
    if(mType == Recv || mQid == -1 || data->size() > mMsgSize) {
        return -EINVAL;
    }

    return mq_send(mQid, (char *)data->toValue(), data->size(), prio);
}

int _PosixMq::send(ByteArray data) {
    return send(data,Priority::Low);
}

int _PosixMq::receive(ByteArray buff) {
    if(mType == Type::Send || buff->size() < mMsgSize) {
        return -EINVAL;
    }

    unsigned int priority = 0;
    return mq_receive(mQid, (char *)buff->toValue(),mMsgSize, &priority);;
}

int _PosixMq::sendTimeout(ByteArray data,long timeInterval,Priority prio) {
    if(mType == Recv || mQid == -1 || data->size() > mMsgSize) {
        return -EINVAL;
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);

    return mq_timedsend(mQid, (char *)data->toValue(), data->size(), prio,&ts);;
}

int _PosixMq::receiveTimeout(ByteArray buff,long timeInterval) {
    if(mType == Send) {
        return -EINVAL;
    }

    struct timespec ts;
    st(System)::getNextTime(timeInterval,&ts);
    unsigned int priority = 0;

    return mq_timedreceive(mQid, (char *)buff->toValue(),mMsgSize, &priority,&ts);
}

int _PosixMq::getMsgSize() {
    return mMsgSize;
}

_PosixMq::~_PosixMq() {
    mq_close(mQid);
}

void _PosixMq::clear() {
    close();
    mq_unlink(mQName->toChars());
}

void _PosixMq::close() {
    mq_close(mQid);
    if(Mq == AutoClone(this)) {
        Mq = nullptr;
    }
}

int _PosixMq::getSystemMqAttr(String path) {
    ByteArray readBuff = createByteArray(32);
    FileInputStream reader = createFileInputStream(path);
    reader->open();
    reader->read(readBuff);
    int ret = readBuff->toString()->toBasicInt();
    reader->close();

    return ret;
}

void _PosixMq::onSigUsr1(int signo) {
    AutoLock l(mMutex);
    mq_notify(Mq->mQid,&Mq->sigev);
    ByteArray data = createByteArray(Mq->getMsgSize());
    int n = Mq->receive(data);
    data->quickShrink(n);
    Mq->mqListener->onData(data);
}


}
