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

namespace obotcha {

class _Message;

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
    
    Mutex mMutex;
    Condition mCondition;
    LinkedList<Message> mMessagePool;
    std::vector<Message> mDelayedMessagePool;

};

}
#endif