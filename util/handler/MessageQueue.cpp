#include "MessageQueue.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

namespace obotcha {

Message _MessageQueue::next() {
    Message msg = nullptr;
    AutoLock l(mMutex);
    while(msg == nullptr && mStatus == 0) {
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
    Inspect(mStatus != 0,-1)

    if (mMessages == nullptr) {
        mMessages = msg;
        mCondition->notify();
        return 0;
    }

    Message p = mMessages;
    Message prev = mMessages;
    bool found = false;
    while(!found) {
        if (p->nextTime > msg->nextTime) {
            if (p == mMessages) {
                msg->next = p;
                mMessages = msg;
            } else {
                prev->next = msg;
                msg->next = p;
            }
            found = true;
        } else {
            prev = p;
            p = p->next;
            if (p == nullptr) {
                prev->next = msg;
                found = true;
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
    return 0;
}

int _MessageQueue::removeMessage(HandlerTarget target,int what) {
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

int _MessageQueue::removeMessage(HandlerTarget target ,Runnable r) {
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
    mStatus = 1;
    Message p = mMessages;
    while (p != nullptr) {
        p->mTarget = nullptr;
        p = p->next;
    }
    mCondition->notifyAll();
}

}