#ifndef __OBOTCHA_MESSAGE_HPP__
#define __OBOTCHA_MESSAGE_HPP__

#include "Object.hpp"
#include "Runnable.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

class _Handler;

DECLARE_CLASS(Message) {
public:
    friend class _Handler;

    _Message();

    _Message(int);

    _Message(Runnable);

    int what;

    int arg1;

    int arg2;

    Object data;

    ~_Message();

private:
    int mType;

    Runnable mRunnable;

    long nextTime;

    sp<_Message> next;
};

} // namespace obotcha
#endif