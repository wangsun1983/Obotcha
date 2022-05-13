#ifndef __OBOTCHA_HTTP_V2_STREAM_SENDER_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_SENDER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
#include "Http2Frame.hpp"
#include "ConcurrentHashMap.hpp"
#include "ConcurrentQueue.hpp"
#include "ByteArray.hpp"
#include "OutputStream.hpp"
#include "Handler.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "List.hpp"
#include "Http2PriorityByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(Http2StreamSender) IMPLEMENTS(Thread){
public:
    _Http2StreamSender(OutputStream);
    void write(Http2PriorityByteArray);
    void close();

private:
    void run();

    Mutex mMutex;
    Condition mCondition;
    List<ConcurrentQueue<ByteArray>> list;
    OutputStream out;
    bool isRunning; //TODO
};

}

#endif
