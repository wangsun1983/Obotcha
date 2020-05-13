#ifndef __OBOTCHA_MESSAGE_HPP__
#define __OBOTCHA_MESSAGE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Runnable.hpp"

namespace obotcha {

class _Handler;

enum MessageInternalType {
    NormalMessage = 1,
    RunnableMessage,
};

DECLARE_SIMPLE_CLASS(MessageData) {
//TODO
};

DECLARE_SIMPLE_CLASS(Message) {

public:
    friend class _Handler;

    _Message();

    _Message(int);

    int what;

    int arg1;

    int arg2;

    MessageData data;

private:
    int mType;
    
    int mDrop;

    Runnable mRunnable;

    long time;

};

}
#endif