#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

namespace obotcha {

#define MESSAGE_POOL_SIZE 32

_Handler::_Handler() {
    mIdleMessagePool = createConcurrentQueue<Message>();

    mMessagePool = createArrayList<Message>();
    
    mIsStop = false;

    mMutex = createMutex("Handler Mutex");

    mCondition = createCondition();

    mDelayedMutex = createMutex("Delayed Mutex");

    start();
}

sp<_Message> _Handler::obtainMessage(int w) {
    Message msg = obtainMessage();
    msg->what = w;
    return msg;
}

sp<_Message> _Handler::obtainMessage() {
    Message msg;
    if(mIdleMessagePool->size() > 0) {
        msg = mIdleMessagePool->deQueueLast();
    } else {
        msg = createMessage();
    }
    return msg;
}

void _Handler::sendEmptyMessage(int what) {
    Message msg = obtainMessage(what);
    msg->mType = NormalMessage;

    sendMessage(msg);
}

void _Handler::sendEmptyMessageDelayed(int what,long delay) {
    long time = st(System)::currentTimeMillis() + delay;
    Message msg = obtainMessage(what);
    msg->mType = NormalMessage;
    msg->time = time + delay;
    AutoMutex l(mDelayedMutex);
    insertDelayedMessage(msg);
    mCondition->notify();
}

void _Handler::sendMessageDelayed(sp<_Message> msg,long delay) {
    long time = st(System)::currentTimeMillis() + delay;
    msg->time = time + delay;
    msg->mType = NormalMessage;
    AutoMutex l(mDelayedMutex);
    insertDelayedMessage(msg);
    mCondition->notify();
}

void _Handler::sendMessage(sp<_Message> msg) {
    msg->mType = NormalMessage;

    AutoMutex l(mMutex);
    mMessagePool->add(msg);
    mCondition->notify();
}

void _Handler::handleMessage(sp<_Message> msg) {
    //do nothing   
}

bool _Handler::hasMessage(int what) {
    {
        AutoMutex l(mMutex);
        ListIterator<Message> iterator = mMessagePool->getIterator();
        while(iterator->hasValue()) {
            if(iterator->getValue()->what == what) {
                return true;
            }

            iterator->next();
        }
    }

    {
        AutoMutex l(mDelayedMutex);
        DelayMessageItem item = mHead;
        
        while(item != nullptr) {
            if(item->msg->what == what) {
                return true;
            }
            item = item->next;
        }
    }

    return false;
}

void _Handler::removeMessages(int what) {
    {
        AutoMutex l(mMutex);
        ListIterator<Message> iterator = mMessagePool->getIterator();
        while(iterator->hasValue()) {
            if(iterator->getValue()->what == what) {
                iterator->getValue()->mDrop = -1;
            }
            iterator->next();
        }
    }

    {
        AutoMutex l(mDelayedMutex);
        DelayMessageItem item = mHead;
        
        while(item != nullptr) {
            DelayMessageItem next = item->next;
            if(item->msg->what == what) {
                removeDelayedMessage(item);
            }
            item = next;
        }
    }
}

void _Handler::run() {
    long waitTime = 0;
    while(!mIsStop) {
        Message msg;
        {
            AutoMutex l(mMutex);
            if(waitTime == 0) {
                waitTime = scanDelayedMessage();
            }
            
            while(mMessagePool->size() == 0) {
                int notifyResult = 0;
                if(waitTime != 0) {
                    notifyResult = mCondition->wait(mMutex,waitTime - st(System)::currentTimeMillis());
                } else {
                    mCondition->wait(mMutex);
                }
                if(notifyResult == -WaitTimeout) {
                    waitTime = scanDelayedMessage();
                }
            }

            msg = mMessagePool->removeAt(0);
        }

         
        if(msg->mDrop == -1) {
            continue;
        }

        switch(msg->mType) {
            case RunnableMessage:{
                Runnable r = msg->mRunnable;
                r->run();
                msg->mRunnable = nullptr;
                break;
            }
            case NormalMessage: {
                handleMessage(msg);
                break;
            }   
        }

        if(mIdleMessagePool->size() < MESSAGE_POOL_SIZE) {
            msg->what = 0;
            msg->arg1 = 0;
            msg->arg2 = 0;
            msg->mType = 0;
            msg->mDrop = 0;
            msg->data = nullptr;
            msg->mRunnable = nullptr;
            mIdleMessagePool->enQueueLast(msg);
        }

        if(waitTime < st(System)::currentTimeMillis()) {
            {
                AutoMutex l(mMutex);
                waitTime = scanDelayedMessage();
            }
        }
    }
}

void _Handler::post(Runnable r) {
    Message msg = obtainMessage();
    msg->mType = RunnableMessage;
    msg->mRunnable = r;
    AutoMutex l(mMutex);
    mMessagePool->add(msg);
    mCondition->notify();
}

void _Handler::postDelayed(Runnable r ,long delay) {
    Message msg = obtainMessage();
    msg->mType = RunnableMessage;
    msg->mRunnable = r;
    msg->time = st(System)::currentTimeMillis() + delay;
    AutoMutex l(mDelayedMutex);
    insertDelayedMessage(msg);
}

void _Handler::insertDelayedMessage(Message msg) {
    if(mHead == nullptr) {
        mHead = createDelayMessageItem();
        mHead->msg = msg;
        mCurrent = mHead;
    } else {
        DelayMessageItem item = createDelayMessageItem();
        item->msg = msg;
        mCurrent->next = item;
        item->prev = mCurrent;
        mCurrent = item;
    }
}
    
long _Handler::scanDelayedMessage() {
    if(mHead == nullptr) {
        return 0;
    }

    long time = st(System)::currentTimeMillis();
    {
        AutoMutex l(mDelayedMutex);
        DelayMessageItem item = mHead;
        long minTime = mHead->msg->time;

        while(item != nullptr) {
            DelayMessageItem next = item->next;
            if(item->msg->time <= time) {
                removeDelayedMessage(item);
                //AutoMutex l(mMutex);
                mMessagePool->add(item->msg);
            } else {
                if(minTime > item->msg->time) {
                    minTime = item->msg->time;
                }
            }

            item = next;
        }
        return minTime;
    }

    return 0;
}

void _Handler::removeDelayedMessage(DelayMessageItem item) {
    if(item == mHead) {
        if(mHead->next != nullptr) {
            mHead = mHead->next;
            mHead->prev = nullptr;
        } else {
            mHead = nullptr;
            mCurrent = nullptr;
        }
    } else if(item == mCurrent){
        mCurrent = item->prev;
        mCurrent->next = nullptr;
    } else {
        item->prev->next = item->next;
        item->next->prev = item->prev;
    }
}

void _Handler::destroy() {
    mIsStop = true;
}

}
