/**
 * @file MessageQueue.cpp
 * @brief Low-level class holding the list of messages to be dispatched by a
 * Looper.  Messages are not added directly to a MessageQueue,
 * but rather through Handler objects associated with the Looper.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2023-01-17
 * @license none
 */
#include "MessageQueue.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

namespace obotcha {

Message _MessageQueue::next() {
    Message msg = nullptr;
    AutoLock l(mMutex);
    while(msg == nullptr && mStatus == Status::Running) {
        if (mMessages == nullptr) {
            mCondition->wait(mMutex);
        } else {
            long interval =
                (mMessages->nextTime - st(System)::CurrentTimeMillis());
            if (interval <= 0) {
                msg = mMessages;
                mMessages = mMessages->next;
                msg->next = nullptr; //remove task link for stack overflow
            } else {
                mCondition->wait(mMutex, interval);
                continue;
            }
        }
    }

    return msg;
}
    
int _MessageQueue::enqueueMessage(Message msg) {
    AutoLock l(mMutex);
    Inspect(mStatus != Status::Running,-1)

    if (mMessages == nullptr) {
        mMessages = msg;
        mCondition->notify();
        return 0;
    }

    Message p = mMessages;
    Message prev = mMessages;
    while(true) {
        if (p->nextTime > msg->nextTime) {
            if (p == mMessages) {
                msg->next = p;
                mMessages = msg;
            } else {
                prev->next = msg;
                msg->next = p;
            }
            break;
        } else {
            prev = p;
            p = p->next;
            if (p == nullptr) {
                prev->next = msg;
                break;
            }
        }
    }
    mCondition->notify();
    return 0;
}

int _MessageQueue::enqueueMessageAtFront(Message msg) {
    AutoLock l(mMutex);
    if (mMessages == nullptr) {
        mMessages = msg;
    } else {
        msg->nextTime = st(System)::CurrentTimeMillis();
        msg->next = mMessages;
        mMessages = msg;
    }
    mCondition->notify();
    return 0;
}

int _MessageQueue::removeMessages(HandlerTarget target,int what) {
    AutoLock l(mMutex);
    Message p = mMessages;
    Message prev = nullptr;
    while (p != nullptr) {
        if (p->what == what && p->mTarget == target) {
            if (mMessages == p) {
                mMessages = mMessages->next;
                p = mMessages;
            } else {
                prev->next = p->next;
                p = p->next;
            }
            continue;
        }

        prev = p;
        p = p->next;
    }

    return 0;
}

int _MessageQueue::removeEqualMessages(HandlerTarget target,int what,Object data) {
    AutoLock l(mMutex);
    Message p = mMessages;
    Message prev = nullptr;
    while (p != nullptr) {
        if (p->what == what && p->mTarget == target && p->data == data) {
            if (mMessages == p) {
                mMessages = mMessages->next;
                p = mMessages;
            } else {
                prev->next = p->next;
                p = p->next;
            }
            continue;
        }

        prev = p;
        p = p->next;
    }

    return 0;
}

int _MessageQueue::removeMessages(HandlerTarget target ,Runnable r) {
    AutoLock l(mMutex);
    Message p = mMessages;
    Message prev = nullptr;
    while (p != nullptr) {
        if (p->mRunnable !=  nullptr 
            && p->mRunnable == r 
            && p->mTarget == target) {
            if (mMessages == p) {
                mMessages = mMessages->next;
                p = mMessages;
            } else {
                prev->next = p->next;
                p = p->next;
            }
            continue;
        }

        prev = p;
        p = p->next;
    }

    return 0;
}

bool _MessageQueue::hasMessage(HandlerTarget target,int what) {
    AutoLock l(mMutex);
    Message p = mMessages;
    while (p != nullptr) {
        if (p->what == what && p->mTarget == target ) {
            return true;
        }
        p = p->next;
    }

    return false;
}

int _MessageQueue::querySize(HandlerTarget target) {
    int count = 0;
    AutoLock l(mMutex);
    Message p = mMessages;
    while (p != nullptr) {
        if (p->mTarget == target ) {
            count++;
        }
        p = p->next;
    }

    return count;
}

void _MessageQueue::quit() {
    AutoLock l(mMutex);
    mStatus = Status::Quit;
    Message p = mMessages;
    while (p != nullptr) {
        p->mTarget = nullptr;
        p = p->next;
    }
    mCondition->notifyAll();
}

}