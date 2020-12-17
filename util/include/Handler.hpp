#ifndef __OBOTCHA_HANDLER_HPP__
#define __OBOTCHA_HANDLER_HPP__

#include <vector>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ArrayList.hpp"
#include "ConcurrentQueue.hpp"
#include "Thread.hpp"

#include "String.hpp"
#include "Runnable.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"
#include "Message.hpp"
#include "Atomic.hpp"

namespace obotcha {

class _Message;

DECLARE_SIMPLE_CLASS(Handler) EXTENDS(Thread){

public:
    _Handler();

    ~_Handler();

    sp<_Message> obtainMessage(int);

    sp<_Message> obtainMessage();

    int sendEmptyMessage(int what);

    int sendEmptyMessageDelayed(int what,long delay);

    int sendMessageDelayed(sp<_Message>,long delay);

    int sendMessage(sp<_Message>);

    virtual void handleMessage(sp<_Message> msg);

    bool hasMessage(int what);

    void removeMessages(int what);

    void run();

    int post(Runnable r);

    int postDelayed(Runnable r,long delay);

    void destroy();

    int size();
    
private:
    enum Status {
        StatusRunning = 0,
        StatusDestroy
    };

    bool isRunning();

    Mutex mMutex;
    Condition mCondition;
    //LinkedList<Message> mMessagePool;
    Message mMessagePool;
    
    Atomic<int> mStatus;
};

}
#endif