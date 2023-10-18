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

    _Message() = default;

    explicit _Message(int what);

    explicit _Message(Runnable);

    int what = -1;

    int arg1 = 0;

    int arg2 = 0;

    Object data;

    void setTarget(sp<_HandlerTarget>);
    sp<_HandlerTarget> getTarget();

    void sendToTarget();

    void setRunnable(Runnable);
    Runnable getRunnable();

    ~_Message() override = default;

private:
    Runnable mRunnable = nullptr;
    sp<_HandlerTarget> mTarget;
    long nextTime = 0;
    sp<_Message> next = nullptr;
};

} // namespace obotcha
#endif