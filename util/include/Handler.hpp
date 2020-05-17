#ifndef __OBOTCHA_HANDLER_HPP__
#define __OBOTCHA_HANDLER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"

#include "String.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "ThreadScheduledPoolExecutor.hpp"

namespace obotcha {

class _Message;

DECLARE_SIMPLE_CLASS(DelayMessageItem) {
public:
    DelayMessageItem next;
    DelayMessageItem prev;
    sp<_Message> msg;
};

DECLARE_SIMPLE_CLASS(Handler) EXTENDS(Thread){

public:
    _Handler();

    sp<_Message> obtainMessage(int);

    sp<_Message> obtainMessage();

    void sendEmptyMessage(int what);

    void sendEmptyMessageDelayed(int what,long delay);

    void sendMessageDelayed(sp<_Message>,long delay);

    void sendMessage(sp<_Message>);

    virtual void handleMessage(sp<_Message> msg);

    bool hasMessage(int what);

    void removeMessages(int what);

    void run();

    void post(Runnable r);

    void postDelayed(Runnable r,long delay);

    void destroy();
    
private:
    void insertDelayedMessage(sp<_Message>);
    
    long scanDelayedMessage();

    void removeDelayedMessage(DelayMessageItem);

    ConcurrentQueue<sp<_Message>> mIdleMessagePool;

    ArrayList<sp<_Message>> mMessagePool;
    
    Mutex mMutex;
    Condition mCondition;
    
    //ArrayList<sp<_Message>> mDelayedMessagePool;
    DelayMessageItem mHead;
    DelayMessageItem mCurrent;
    Mutex mDelayedMutex;
    
    mutable volatile bool mIsStop;
};

}
#endif