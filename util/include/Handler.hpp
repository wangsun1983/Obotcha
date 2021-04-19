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
#include "AtomicInteger.hpp"

namespace obotcha {

class _Message;

DECLARE_SIMPLE_CLASS(Handler) IMPLEMENTS(Thread){

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
    
    template<typename X>
    int post(sp<X> r) {
        return postDelayed(0,r);
    }

    template< class Function, class... Args >
    int post(Function&& f, Args&&... args) {
        return postDelayed(0,createLambdaRunnable(f,args...));
    }

    template<typename X>
    int postDelayed(long delay,sp<X> r) {
        Message msg = obtainMessage();
        msg->mRunnable = r;
        return sendMessageDelayed(msg,delay);
    }

    template< class Function, class... Args >
    int postDelayed(long delay,Function&& f, Args&&... args) {
        return postDelayed(delay,createLambdaRunnable(f,args...));
    }
    
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
    
    AtomicInteger mStatus;
};

}
#endif