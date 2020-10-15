#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

namespace obotcha {

#define MESSAGE_POOL_SIZE 32

_Handler::_Handler() {
    mMutex = createMutex("HandlerMutex");
    mCondition = createCondition();
    mMessagePool = createLinkedList<Message>();

    start();
}

sp<_Message> _Handler::obtainMessage(int w) {
    Message msg = obtainMessage();
    msg->what = w;
    return msg;
}

sp<_Message> _Handler::obtainMessage() {
    return createMessage();
}

void _Handler::sendEmptyMessage(int what) {
    Message msg = obtainMessage(what);
    sendMessage(msg);
}

void _Handler::sendMessage(sp<_Message> msg) {
    AutoLock l(mMutex);
    mMessagePool->enQueueLast(msg);
    mCondition->notify();
}

void _Handler::sendEmptyMessageDelayed(int what,long delay) {
    Message msg = createMessage(what);
    sendMessageDelayed(msg,delay);
}

void _Handler::sendMessageDelayed(sp<_Message> msg,long delay) {
    msg->nextTime = st(System)::currentTimeMillis() + delay;

    AutoLock l(mMutex);
    int start = 0;
    int end = mDelayedMessagePool.size() - 1;

    int index = 0;
    bool isNeedInsert = true;
    while(start <= end) {
        index = (start+end)/2;
        long time = mDelayedMessagePool.at(index)->nextTime;
        if(time > msg->nextTime) {
            end = index - 1;
        } else if(time < msg->nextTime) {
            start = index + 1;
        } else if(time == msg->nextTime) {
            break;
        }
    }

    mDelayedMessagePool.insert(mDelayedMessagePool.begin() + index,msg);
    mCondition->notify();
}

void _Handler::handleMessage(sp<_Message> msg) {
    //do nothing
}

bool _Handler::hasMessage(int what) {
    AutoLock l(mMutex);
    LinkedListIterator<Message> iterator = mMessagePool->getIterator();
    while(iterator->hasValue()) {
        Message msg = iterator->getValue();
        if(msg->what == what) {
            return true;
        }
        iterator->next();
    }

    for(int i = 0;i < mDelayedMessagePool.size();i++) {
        if(mDelayedMessagePool[i]->what == what) {
            return true;
        }
    }
    return false;
}

void _Handler::removeMessages(int what) {
    AutoLock l(mMutex);
    LinkedListIterator<Message> iterator = mMessagePool->getIterator();
    while(iterator->hasValue()) {
        Message msg = iterator->getValue();
        if(msg->what == what) {
            iterator->remove();
            continue;
        }
        iterator->next();
    }
    
    auto iterator2 = mDelayedMessagePool.begin();
    while(iterator2 != mDelayedMessagePool.end()) {
        Message msg = *iterator2;
        if(msg->what == what) {
            iterator2 = mDelayedMessagePool.erase(iterator2);
        } else {
            iterator2++;
        }
    }
}

void _Handler::run() {
    long waitTime = 0;
    while(1) {
        Message msg = nullptr;
        {
            AutoLock l(mMutex);
            if(mDelayedMessagePool.size() != 0) {
                if(mDelayedMessagePool[0]->nextTime <= st(System)::currentTimeMillis()) {
                msg = *mDelayedMessagePool.erase(mDelayedMessagePool.begin());
                }
            } else if(!mMessagePool->isEmpty()) {
                msg = mMessagePool->deQueueFirst();
            }

            if(msg == nullptr) {
                if(mDelayedMessagePool.size() != 0) {
                    long interval = (mDelayedMessagePool[0]->nextTime - st(System)::currentTimeMillis());
                    if(interval >= 0) {
                        mCondition->wait(mMutex,interval);
                    }
                } else {
                    mCondition->wait(mMutex);
                }
                continue;
            }
        }

        if(msg != nullptr) {
            if(msg->mRunnable == nullptr) {
                handleMessage(msg);
            } else {
                msg->mRunnable->run();
            }
        }
    }
}

void _Handler::post(Runnable r) {
    Message msg = obtainMessage();
    msg->mRunnable = r;
    sendMessage(msg);
}

void _Handler::postDelayed(Runnable r ,long delay) {
    Message msg = obtainMessage();
    sendMessageDelayed(msg,delay);
}

void _Handler::destroy() {
    //TODO
}

}
