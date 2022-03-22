#ifndef __OBOTCHA_REDIS_CONNECTION_H__
#define __OBOTCHA_REDIS_CONNECTION_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "hiredis.h"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "async.h"
#include "HashMap.hpp"
#include "HashSet.hpp"
extern "C" {
#include "ae.h"
}

namespace obotcha {

DECLARE_CLASS(RedisSubscribeListener) {
public:
    virtual void onEvent(String,String) = 0;
};

DECLARE_CLASS(RedisConnection) {

public:
    _RedisConnection();
    int connect(String server,int port,long millseconds);
    int set(String,String);
    int set(String,int);

    int del(String);
    
    String get(String);
    int inc(String);
    int dec(String);

    int set(String,ArrayList<String>);

    int subscribe(String,RedisSubscribeListener);
    int desubscribe(String,RedisSubscribeListener);

    int publish(String,String);

    ~_RedisConnection();

private:
    void _InitAsyncContext();
    static void commandCallback(redisAsyncContext *redis_context,void *reply, void *privdata);

    redisContext *mContext;
    redisAsyncContext *aSyncContext;
    struct event_base *base;
    Mutex mMutex;

    HashMap<String,HashSet<RedisSubscribeListener>> mChannelListeners;
    String mServer;
    int mPort;

    struct aeEventLoop *loop;
    Thread loopThread;
};

} // namespace obotcha
#endif