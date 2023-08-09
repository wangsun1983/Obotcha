#ifndef __OBOTCHA_MESSAGE_QUEUE_HPP__
#define __OBOTCHA_MESSAGE_QUEUE_HPP__

#include <atomic>

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

    int removeMessage(HandlerTarget,int what);
    int removeMessage(HandlerTarget,Runnable);
    bool hasMessage(HandlerTarget,int what);

    int querySize(HandlerTarget);
    void quit();

private:
    Mutex mMutex = createMutex();;
    Condition mCondition = createCondition();
    Message mMessages;
    std::atomic<int32_t> mStatus = 0;
};

} // namespace obotcha
#endif