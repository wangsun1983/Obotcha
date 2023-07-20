#include <mutex>
#include <mqueue.h>
#include <signal.h>

#include "ProcessMq.hpp"
#include "System.hpp"
#include "InitializeException.hpp"
#include "FileInputStream.hpp"
#include "Log.hpp"
#include "AutoLock.hpp"

namespace obotcha {

int _ProcessMq::MaxMsgNums = -1;
int _ProcessMq::MaxMsgSize = -1;

//ProcessMqListenerLambda
_ProcessMqListenerLambda::_ProcessMqListenerLambda(_ProcessMqLambda f) {
    func = f;
}

void _ProcessMqListenerLambda::onData(ByteArray data) {
    func(data);
}

_ProcessMq::_ProcessMq(String name,int type,int msgsize,int maxmsgs) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [this]() {
        MaxMsgNums = getSystemMqAttr("/proc/sys/fs/mqueue/msg_max");
        MaxMsgSize = getSystemMqAttr("/proc/sys/fs/mqueue/msgsize_max");
    });

    if(maxmsgs > MaxMsgNums || msgsize > MaxMsgSize) {
        Trigger(InitializeException,"invald param");
    }

    mQueueName = name->startsWith("/")?name:createString("/")->append(name);
    
    mMaxMsgs = maxmsgs;
    mMsgSize = msgsize;

    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = mMaxMsgs;
    mqAttr.mq_msgsize = mMsgSize;
    uint64_t flag = O_RDWR|O_CREAT|O_EXCL;
    if(type == AsyncSend || type == AsyncRecv) {
        flag |= O_NONBLOCK;
    }

    mQid = mq_open(mQueueName->toChars(), flag , S_IWUSR|S_IRUSR, &mqAttr);
    if (mQid < 0) {
        if (errno == EEXIST) {
            flag &= ~O_CREAT;
            mQid = mq_open(mQueueName->toChars(), flag ,&mqAttr);
        }
    }

    mq_getattr(mQid, &mqAttr);
    if(mqAttr.mq_maxmsg != mMaxMsgs || mqAttr.mq_msgsize != mMsgSize) {
        mq_close(mQid);
        mQid = -1;
        Trigger(InitializeException,"open msg queue failed");
    }
}

_ProcessMq::_ProcessMq(String name,ProcessMqListener listener,int msgsize,int maxmsgs)
            :_ProcessMq(name,AsyncRecv,msgsize,maxmsgs) {
    mqListener = listener;
    mSigev.sigev_notify = SIGEV_THREAD;
    mSigev.sigev_notify_function = onData;
    mSigev.sigev_value.sival_ptr = this;
    mSigev.sigev_notify_attributes = nullptr;
    mq_notify(mQid,&mSigev);
}

_ProcessMq::_ProcessMq(String name,_ProcessMqLambda l,int msgsize,int maxmsgs):_ProcessMq(name,createProcessMqListenerLambda(l),msgsize,maxmsgs) {
    
}

int _ProcessMq::send(ByteArray data,Priority prio) {
    if(mType == Recv || mQid == -1 || data->size() > mMsgSize) {
        return -EINVAL;
    }

    int ret = 0;
    while(1) {
        ret = mq_send(mQid, (char *)data->toValue(), data->size(), 1);
        if(ret < 0 && errno == EAGAIN) {
            usleep(1000*100);
            continue;
        }
        break;
    }

    return ret;
}

int _ProcessMq::send(ByteArray data) {
    return send(data,Priority::Low);
}

int _ProcessMq::receive(ByteArray buff) {
    if(mType == Type::Send || buff->size() < mMsgSize) {
        return -EINVAL;
    }

    unsigned int priority = 0;
    return mq_receive(mQid, (char *)buff->toValue(),mMsgSize, &priority);;
}

int _ProcessMq::sendTimeout(ByteArray data,long timeInterval,Priority prio) {
    if(mType == Recv || mQid == -1 || data->size() > mMsgSize) {
        return -EINVAL;
    }

    struct timespec ts;
    st(System)::GetNextTime(timeInterval,&ts);
    return mq_timedsend(mQid, (char *)data->toValue(), data->size(), prio,&ts);;
}

int _ProcessMq::receiveTimeout(ByteArray buff,long timeInterval) {
    if(mType == Send) {
        return -EINVAL;
    }

    struct timespec ts;
    st(System)::GetNextTime(timeInterval,&ts);
    unsigned int priority = 0;

    return mq_timedreceive(mQid, (char *)buff->toValue(),mMsgSize, &priority,&ts);
}

int _ProcessMq::getMsgSize() {
    return mMsgSize;
}

_ProcessMq::~_ProcessMq() {
    mq_close(mQid);
}

void _ProcessMq::clear() {
    close();
    mq_unlink(mQueueName->toChars());
}

void _ProcessMq::close() {
    mq_close(mQid);
}

int _ProcessMq::getSystemMqAttr(String path) {
    ByteArray readBuff = createByteArray(32);
    FileInputStream reader = createFileInputStream(path);
    reader->open();
    reader->read(readBuff);
    int ret = readBuff->toString()->toBasicInt();
    reader->close();
    return ret;
}

void _ProcessMq::onData(union sigval sig) {
    ProcessMq mq = AutoClone((_ProcessMq *)sig.sival_ptr);
    mq_notify(mq->mQid,&mq->mSigev);
    ByteArray data = createByteArray(mq->getMsgSize());
    int n = mq->receive(data);
    data->quickShrink(n);
    mq->mqListener->onData(data);
}


}
