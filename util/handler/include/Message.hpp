#ifndef __OBOTCHA_MESSAGE_HPP__
#define __OBOTCHA_MESSAGE_HPP__

#include "Object.hpp"
#include "Runnable.hpp"

namespace obotcha {

class _Handler;
class _HandlerTarget;
class _MessageQueue;

DECLARE_CLASS(Message) {
public:
    friend class _Handler;
    friend class _MessageQueue;

    _Message();

    _Message(int);

    _Message(Runnable);

    int what;

    int arg1;

    int arg2;

    Object data;

    void setTarget(sp<_HandlerTarget>);
    sp<_HandlerTarget> getTarget();

    void setRunnable(Runnable);
    Runnable getRunnable();

    ~_Message();

private:
 

    int mType;
    Runnable mRunnable;
    sp<_HandlerTarget> mTarget;

    long nextTime;
    sp<_Message> next;
};

} // namespace obotcha
#endif