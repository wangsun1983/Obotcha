/**
 * @file Handler.hpp
 * @brief A Handler allows you to send and process and Runnable
 *        objects associated with a thread's MessageQueue.
 *        Each Handler instance is associated with a single thread.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */


#ifndef __OBOTCHA_HANDLER_HPP__
#define __OBOTCHA_HANDLER_HPP__

#include <vector>

#include "ArrayList.hpp"
#include "ConcurrentQueue.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"

#include "AtomicInteger.hpp"
#include "Condition.hpp"
#include "LinkedList.hpp"
#include "Message.hpp"
#include "Mutex.hpp"
#include "Runnable.hpp"
#include "String.hpp"

namespace obotcha {

class _Message;

DECLARE_CLASS(Handler) IMPLEMENTS(Thread) {
public:
    _Handler();

    ~_Handler();

    sp<_Message> obtainMessage(int);

    sp<_Message> obtainMessage();

    int sendEmptyMessage(int what);

    int sendEmptyMessageDelayed(int what, long delay);

    int sendMessageDelayed(sp<_Message>, long delay);

    int sendMessage(sp<_Message>);

    int sendMessageAtFrontOfQueue(Message msg);

    virtual void handleMessage(sp<_Message> msg);

    bool hasMessage(int what);

    void removeMessages(int what);

    void removeCallbacks(sp<_Runnable> r);

    template <typename X> int post(sp<X> r) { 
        return postDelayed(0, r); 
    }

    template <class Function, class... Args>
    int post(Function && f, Args && ... args) {
        return postDelayed(0, createLambdaRunnable(f, args...));
    }

    template <typename X> int postDelayed(long delay, sp<X> r) {
        Message msg = obtainMessage();
        msg->mRunnable = r;
        return sendMessageDelayed(msg, delay);
    }

    template <class Function, class... Args>
    int postDelayed(long delay, Function &&f, Args &&... args) {
        return postDelayed(delay, createLambdaRunnable(f, args...));
    }

    void release();

    int size();

private:
    bool isRunning();
    void run();

    Mutex mMutex;
    Condition mCondition;
    Message mMessagePool;

    //AtomicInteger mStatus;
    volatile bool mIsRunning;
};

} // namespace obotcha
#endif