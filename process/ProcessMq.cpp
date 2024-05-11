#include <mutex>
#include <mqueue.h>
#include <signal.h>
#include <limits.h>

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

_ProcessMq::_ProcessMq(String name,const bool async,int msgsize,int maxmsgs):mMsgSize(msgsize),mMaxMsgs(maxmsgs) {
    static std::once_flag s_flag;
    std::call_once(s_flag, [this]() {
        MaxMsgNums = getSystemMqAttr("/proc/sys/fs/mqueue/msg_max");
        MaxMsgSize = getSystemMqAttr("/proc/sys/fs/mqueue/msgsize_max");
    });

    if(maxmsgs > MaxMsgNums || msgsize > MaxMsgSize) {
        Trigger(InitializeException,"invald param")
    }

    mQueueName = name->startsWith("/")?name:String::New("/")->append(name);
    struct mq_attr mqAttr;
    mqAttr.mq_maxmsg = mMaxMsgs;
    mqAttr.mq_msgsize = mMsgSize;
    int flag = O_RDWR|O_CREAT|O_EXCL;
    if(async) {
        flag |= O_NONBLOCK;
    }

    mQid = mq_open(mQueueName->toChars(), flag , S_IWUSR|S_IRUSR, &mqAttr);
    if (mQid < 0) {
        if (errno == EEXIST) {
            flag &= ~O_CREAT;
            mQid = mq_open(mQueueName->toChars(), flag ,&mqAttr);
        } else {
            Trigger(InitializeException,"open msg failed!!!")
        }
    }

    mq_getattr(mQid, &mqAttr);
    if(mqAttr.mq_maxmsg != mMaxMsgs || mqAttr.mq_msgsize != mMsgSize) {
        mq_close(mQid);
        mQid = -1;
        Trigger(InitializeException,"open msg queue failed")
    }
}

void _ProcessMq::setListener(ProcessMqListener listener) {
    mqListener = listener;
    mSigev.sigev_notify = SIGEV_THREAD;
    mSigev.sigev_notify_function = onData;
    mSigev.sigev_value.sival_ptr = this;
    mSigev.sigev_notify_attributes = nullptr;
    mq_notify(mQid,&mSigev);
}

void _ProcessMq::setListener(const _ProcessMqLambda &l) {
    setListener(ProcessMqListenerLambda::New(l));
}

ssize_t _ProcessMq::send(ByteArray data,int prio) const {
    if(mQid == -1 || data->size() > mMsgSize || prio >= MQ_PRIO_MAX) {
        return -EINVAL;
    }

    int ret = 0;
    while(true) {
        ret = mq_send(mQid, (char *)data->toValue(), data->size(), prio);
        if(ret < 0 && errno == EAGAIN) {
            st(System)::Sleep(100);
            continue;
        }
        break;
    }

    return ret;
}

ssize_t _ProcessMq::receive(ByteArray buff) const {
    if(buff->size() < mMsgSize) {
        return -EINVAL;
    }

    unsigned int priority = 0;
    return mq_receive(mQid, (char *)buff->toValue(),mMsgSize, &priority);
}

ssize_t _ProcessMq::sendTimeout(ByteArray data,long timeInterval,int prio) const {
    if(mQid == -1 || data->size() > mMsgSize) {
        return -EINVAL;
    }

    struct timespec ts;
    st(System)::GetNextTime(timeInterval,&ts);
    return mq_timedsend(mQid, (char *)data->toValue(), data->size(), prio,&ts);
}

ssize_t _ProcessMq::receiveTimeout(ByteArray buff,long timeInterval) const {
    struct timespec ts;
    st(System)::GetNextTime(timeInterval,&ts);
    unsigned int priority = 0;

    return mq_timedreceive(mQid, (char *)buff->toValue(),mMsgSize, &priority,&ts);
}

int _ProcessMq::getMsgSize() const {
    return mMsgSize;
}

_ProcessMq::~_ProcessMq() {
    mq_close(mQid);
}

void _ProcessMq::clear() {
    close();
    mq_unlink(mQueueName->toChars());
}

void _ProcessMq::close() const {
    mq_close(mQid);
}

int _ProcessMq::getSystemMqAttr(String path) const {
    ByteArray readBuff = ByteArray::New(32);
    FileInputStream reader = FileInputStream::New(path);
    reader->open();
    reader->read(readBuff);
    int ret = readBuff->toString()->toBasicInt();
    reader->close();
    return ret;
}

void _ProcessMq::onData(union sigval sig) {
    ProcessMq mq = AutoClone((_ProcessMq *)sig.sival_ptr);
    mq_notify(mq->mQid,&mq->mSigev);
    ByteArray data = ByteArray::New(mq->getMsgSize());
    int n = mq->receive(data);
    data->quickShrink(n);
    mq->mqListener->onData(data);
}


}
