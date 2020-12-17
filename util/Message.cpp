/**
 * @file Message.cpp
 * @brief Defines a message containing a description and arbitrary data object that 
 *        can be sent to a handler.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include "Message.hpp"

namespace obotcha {

_Message::_Message() {
    nextTime = 0;
    next = nullptr;
    mRunnable = nullptr;
}

_Message::_Message(int w) {
    what = w;
    nextTime = 0;
    next = nullptr;
    mRunnable = nullptr;
}

_Message::_Message(Runnable r) {
    mRunnable = r;
    nextTime = 0;
    next = nullptr;
}

_Message::~_Message() {
    //TODO
}

}
