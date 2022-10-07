/**
 * @file Message.cpp
 * @brief  A Handler allows you to send and process Message and Runnable objects
 * associated with a thread
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Handler.hpp"
#include "Message.hpp"
#include "String.hpp"
#include "System.hpp"

namespace obotcha {

/**
 * Default constructor
 */
_Handler::_Handler() {
    mMutex = createMutex("HandlerMutex");
    mCondition = createCondition();
    mMessagePool = nullptr;
    mIsRunning = true;
    start();
}

_Handler::~_Handler() {
    release();
    join();
}

sp<_Message> _Handler::obtainMessage(int w) {
    Message msg = obtainMessage();
    msg->what = w;
    return msg;
}

sp<_Message> _Handler::obtainMessage() { 
    return createMessage(-1); 
}

int _Handler::sendEmptyMessage(int what) {
    Message msg = createMessage(what);
    return sendMessage(msg);
}

int _Handler::sendMessage(sp<_Message> msg) {
    return sendMessageDelayed(msg, 0);
}

int _Handler::sendEmptyMessageDelayed(int what, long delay) {
    Message msg = createMessage(what);
    return sendMessageDelayed(msg, delay);
}

int _Handler::sendMessageDelayed(sp<_Message> msg, long delay) {
    msg->nextTime = st(System)::currentTimeMillis() + delay;
    AutoLock l(mMutex);
    if(!mIsRunning) {
        return -1;
    }

    if (mMessagePool == nullptr) {
        mMessagePool = msg;
    } else {
        Message p = mMessagePool;
        Message prev = mMessagePool;
        for (;;) {
            if (p->nextTime > msg->nextTime) {
                if (p == mMessagePool) {
                    msg->next = p;
                    mMessagePool = msg;
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
    }
    mCondition->notify();

    return 0;
}

int _Handler::sendMessageAtFrontOfQueue(Message msg) {
    AutoLock l(mMutex);
    if (mMessagePool == nullptr) {
        mMessagePool = msg;
    } else {
        msg->nextTime = st(System)::currentTimeMillis();
        msg->next = mMessagePool;
        mMessagePool = msg;
    }

    return 1;
}

void _Handler::handleMessage(sp<_Message> msg) {
    // do nothing
}

bool _Handler::hasMessage(int what) {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    while (p != nullptr) {
        if (p->what == what) {
            return true;
        }
        p = p->next;
    }

    return false;
}

void _Handler::removeMessages(int what) {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    Message prev = nullptr;
    while (p != nullptr) {
        if (p->what == what) {
            if (mMessagePool == p) {
                mMessagePool = mMessagePool->next;
                p = mMessagePool;
            } else {
                prev->next = p->next;
                p = p->next;
            }
            continue;
        }

        prev = p;
        p = p->next;
    }
}

void _Handler::removeCallbacks(sp<_Runnable> r) {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    Message prev = nullptr;
    while (p != nullptr) {
        if (p->mRunnable == r) {
            if (mMessagePool == p) {
                mMessagePool = mMessagePool->next;
                p = mMessagePool;
            } else {
                prev->next = p->next;
                p = p->next;
            }
            continue;
        }

        prev = p;
        p = p->next;
    }   
}

void _Handler::run() {
    while (1) {
        Message msg = nullptr;
        {
            AutoLock l(mMutex);
            if(!mIsRunning) {
                break;
            }

            if (mMessagePool == nullptr) {
                mCondition->wait(mMutex);
                continue;
            } else {
                long interval =
                    (mMessagePool->nextTime - st(System)::currentTimeMillis());
                if (interval <= 0) {
                    msg = mMessagePool;
                    mMessagePool = mMessagePool->next;
                    msg->next = nullptr; //remove task link for stack overflow
                } else {
                    mCondition->wait(mMutex, interval);
                    continue;
                }
            }
        }
        if (msg != nullptr) {
            (msg->mRunnable == nullptr)?handleMessage(msg):msg->mRunnable->run();
        }
    }
}

void _Handler::release() {
    AutoLock l(mMutex);
    if(mIsRunning) {
        mIsRunning = false;
        mCondition->notify();
    }
}

bool _Handler::isRunning() {
    AutoLock l(mMutex);
    return mIsRunning; 
}

int _Handler::size() {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    int size = 0;
    while (p != nullptr) {
        size++;
        p = p->next;
    }

    return size;
}

} // namespace obotcha
