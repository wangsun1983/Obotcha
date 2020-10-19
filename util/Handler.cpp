#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "Handler.hpp"
#include "Message.hpp"
#include "System.hpp"

namespace obotcha {

const int _Handler::StatusRunning = 1;
const int _Handler::StatusDestroy = 2;

_Handler::_Handler() {
    mMutex = createMutex("HandlerMutex");
    mCondition = createCondition();
    mMessagePool = nullptr;
    mStatus = StatusRunning;
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

int _Handler::sendEmptyMessage(int what) {
    Message msg = obtainMessage(what);
    return sendMessage(msg);
}

int _Handler::sendMessage(sp<_Message> msg) {
    return sendMessageDelayed(msg,0);
}

int _Handler::sendEmptyMessageDelayed(int what,long delay) {
    Message msg = createMessage(what);
    sendMessageDelayed(msg,delay);
}

int _Handler::sendMessageDelayed(sp<_Message> msg,long delay) {
    if(mStatus != StatusRunning) {
        return -1;
    }

    msg->nextTime = st(System)::currentTimeMillis() + delay;
    AutoLock l(mMutex);
    if(mMessagePool == nullptr) {
        mMessagePool = msg;
    } else {
        Message p = mMessagePool;
        Message prev = nullptr;
        for (;;) {
            if(p->nextTime > msg->nextTime) {
                if(p == mMessagePool) {
                    msg->next = p;
                    mMessagePool = msg;
                } else {
                    prev->next = msg;
                    msg->next = p;
                }
                break;
            } else {
                if(p->next == nullptr) {
                    p->next = msg;
                    break;
                } else {
                    prev = p;
                    p = p->next;
                }
            }
        }
    }

    mCondition->notify();

    return 0;
}

void _Handler::handleMessage(sp<_Message> msg) {
    //do nothing
}

bool _Handler::hasMessage(int what) {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    while(p != nullptr) {
        if(p->what == what) {
            return true;
        }
    }

    return false;
}

void _Handler::removeMessages(int what) {
    AutoLock l(mMutex);
    Message p = mMessagePool;
    Message prev = nullptr;
    while(p != nullptr) {
        if(p->what == what) {
            if(mMessagePool == p) {
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
    long waitTime = 0;
    while(mStatus != StatusDestroy) {
        Message msg = nullptr;
        printf("handler run trace1 \n");
        {
            AutoLock l(mMutex);
            if(mMessagePool == nullptr) {
                mCondition->wait(mMutex);
                continue;
            }else if(mMessagePool != nullptr) {
                long interval = (mMessagePool->nextTime - st(System)::currentTimeMillis());
                if(interval <= 0) {
                    msg = mMessagePool;
                    mMessagePool = mMessagePool->next;
                } else {
                    mCondition->wait(mMutex,interval);
                    continue;
                }
            }
        }

        if(msg != nullptr) {
            if(msg->mRunnable == nullptr) {
                printf("handler run trace8 \n");
                handleMessage(msg);
            } else {
                printf("handler run trace9 \n");
                msg->mRunnable->run();
            }
        }
    }
}

int _Handler::post(Runnable r) {
    return postDelayed(r,0);
}

int _Handler::postDelayed(Runnable r ,long delay) {
    Message msg = obtainMessage();
    msg->mRunnable = r;
    return sendMessageDelayed(msg,delay);
}

void _Handler::destroy() {
    mStatus = StatusDestroy;
    quit();
}

bool _Handler::isRunning() {
    return mStatus == StatusRunning;
}

}
