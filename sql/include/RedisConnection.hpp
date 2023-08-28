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
#include "EPollObserver.hpp"
#include "Redis.hpp"

namespace obotcha {

DECLARE_CLASS(RedisSubscribeListener) {
public:
    virtual void onEvent(st(Redis)::Event type,String,String) = 0;
};

using _RedisSubscribeLambda = std::function<void(st(Redis)::Event,String,String)>;
DECLARE_CLASS(LambdaRedisSubscribeListener) IMPLEMENTS (RedisSubscribeListener) {
public:
    explicit _LambdaRedisSubscribeListener(_RedisSubscribeLambda f){
        func = f;
    }

    void onEvent(st(Redis)::Event event,String key,String value) {
        func(event,key,value);
    }

    ~_LambdaRedisSubscribeListener() = default;

private:
    _RedisSubscribeLambda func;
};

DECLARE_CLASS(RedisConnection) IMPLEMENTS(EPollListener) {

public:
    _RedisConnection() = default;
    int connect(String server,int port,long millseconds);
    int set(String,String);
    int set(String,int);

    int del(String);
    
    String get(String);
    long long inc(String);
    long long dec(String);

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
    
    void _onEventTrigger(st(Redis)::Event,String,String);

    st(IO)::Epoll::Result onEvent(int fd, uint32_t events);

    EPollObserver mEpoll;
    
    redisContext *mContext = nullptr;
    redisAsyncContext *aSyncContext = nullptr;

    Mutex mMutex = createMutex();

    bool isInLooper = false;
    HashMap<String,HashSet<RedisSubscribeListener>> mChannelListeners;
    String mServer;
    int mPort;
};

} // namespace obotcha
#endif