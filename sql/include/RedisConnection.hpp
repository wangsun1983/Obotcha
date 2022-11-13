#ifndef __OBOTCHA_REDIS_CONNECTION_H__
#define __OBOTCHA_REDIS_CONNECTION_H__

#include "hiredis.h"
#include "async.h"

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "Mutex.hpp"
#include "HashMap.hpp"
#include "HashSet.hpp"
#include "EPollFileObserver.hpp"

namespace obotcha {

DECLARE_CLASS(RedisSubscribeListener) {
public:
    virtual void onEvent(int type,String,String) = 0;
};

using _RedisSubscribeLambda = std::function<void(int,String,String)>;
DECLARE_CLASS(LambdaRedisSubscribeListener) IMPLEMENTS (RedisSubscribeListener) {
public:
    _LambdaRedisSubscribeListener(_RedisSubscribeLambda f){
        func = f;
    }

    void onEvent(int type,String key,String value) {
        func(type,key,value);
    }

    ~_LambdaRedisSubscribeListener() {
        // do nothing
    }

private:
    _RedisSubscribeLambda func;
};

DECLARE_CLASS(RedisConnection) IMPLEMENTS(EPollFileObserverListener) {

public:
    enum RedisEvent {
        Message = 0,
        Subscribe,
        UnSubscribe,
    };

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
    int subscribe(String key,_RedisSubscribeLambda);
    int unsubscribe(String,RedisSubscribeListener);

    int publish(String,String);

    int close();
    ~_RedisConnection();

private:
    void _InitAsyncContext();
    static void _RedisAddRead(void * c);
    static void _RedisDelRead(void * c);
    static void _RedisAddWrite(void * c);
    static void _RedisDelWrite(void * c);
    static void _RedisCleanup(void * c);
    static void _CommandCallback(redisAsyncContext *redis_context,void *reply, void *privdata);
    
    void _onEventTrigger(int,String,String);

    int onEvent(int fd, uint32_t events);

    EPollFileObserver mEpoll;
    
    redisContext *mContext;
    redisAsyncContext *aSyncContext;

    Mutex mMutex;

    bool isInLooper;
    HashMap<String,HashSet<RedisSubscribeListener>> mChannelListeners;
    String mServer;
    int mPort;
};

} // namespace obotcha
#endif