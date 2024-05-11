/**
 * @file MessageQueue.hpp
 * @brief Low-level class holding the list of messages to be dispatched by a
 *        looper.Messages are not added directly to a MessageQueue,but rather 
 *        through Handler objects associated with the Looper.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */

#ifndef __OBOTCHA_MESSAGE_QUEUE_HPP__
#define __OBOTCHA_MESSAGE_QUEUE_HPP__

#include "Object.hpp"
#include "Condition.hpp"
#include "Message.hpp"
#include "Mutex.hpp"
#include "Runnable.hpp"
#include "HandlerTarget.hpp"

namespace obotcha {

class _Message;

DECLARE_CLASS(MessageQueue) {
public:
    _MessageQueue() = default;
    Message next();
    int enqueueMessage(Message msg);
    int enqueueMessageAtFront(Message msg);

    int removeMessages(HandlerTarget,int what);
    int removeMessages(HandlerTarget,Runnable);
    int removeEqualMessages(HandlerTarget,int what,Object data);

    bool hasMessage(HandlerTarget,int what);

    int querySize(HandlerTarget);
    void quit();

private:
    enum class Status {
        Running = 0,
        Quit,
    };

    Mutex mMutex = Mutex::New();;
    Condition mCondition = Condition::New();
    Message mMessages;
    Status mStatus = Status::Running;
};

} // namespace obotcha
#endif