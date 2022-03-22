#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "RedisConnection.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"

namespace obotcha {
//http://doc.redisfans.com/

_RedisConnection::_RedisConnection() {
    mMutex = createMutex();
    aSyncContext = nullptr;
    mContext = nullptr;
}

int _RedisConnection::connect(String server,int port,long millseconds) {
    mServer = server;
    mPort = port;
    struct timeval timeout = { millseconds/1000, (millseconds%1000)*1000 };
    mContext = redisConnectWithTimeout(mServer->toChars(), mPort, timeout);
    if (mContext == nullptr || mContext->err) {
        if (mContext) {
            LOG(ERROR)<<"Connection error: "<<mContext->errstr;
            redisFree(mContext);
        } else {
            LOG(ERROR)<<"Connection fail ";
        }
        Trigger(InitializeException,"redis connect fail");
    }

    return 0;
}

int _RedisConnection::set(String key,String value) {
    redisReply *reply = (redisReply *)redisCommand(mContext,"SET %b %b", key->toChars(),key->size(),value->toChars(),value->size());
    if(reply == nullptr) {
        return -1;
    }

    freeReplyObject(reply);
    return 0;
}

int _RedisConnection::set(String key,int value) {
    redisReply *reply = (redisReply *)redisCommand(mContext,"SET %b %d", key->toChars(),key->size(),value);
    if(reply == nullptr) {
        return -1;
    }

    freeReplyObject(reply);
    return 0;
}

int _RedisConnection::del(String key) {
    redisReply *reply = (redisReply *)redisCommand(mContext,"DEL %b", key->toChars(),key->size());
    if(reply == nullptr) {
        return -1;
    }

    freeReplyObject(reply);
    return 0;
}

String _RedisConnection::get(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"GET %s",key->toChars());
    if(reply == nullptr || reply->str == nullptr) {
        return nullptr;
    }
    String value = createString(reply->str);
    freeReplyObject(reply);
    return value;
}

int _RedisConnection::inc(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"INCR %s",key->toChars());
    int value = reply->integer;
    freeReplyObject(reply);
    return value;
}

int _RedisConnection::dec(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"DECR %s",key->toChars());
    int value = reply->integer;
    freeReplyObject(reply);
    return value;
}

int _RedisConnection::set(String key,ArrayList<String> list){
    ListIterator<String> iterator = list->getIterator();
    while(iterator->hasValue()) {
        redisReply * reply = (redisReply *)redisCommand(mContext,"LPUSH %s element-%s",key->toChars(),iterator->getValue()->toChars());
        freeReplyObject(reply);
        iterator->next();
    }
    return 0;
}

_RedisConnection::~_RedisConnection() {
    if(mContext != nullptr) {
        redisFree(mContext);
        mContext = nullptr;
    }
}

void _RedisConnection::_InitAsyncContext() {
    AutoLock l(mMutex);
    if(aSyncContext == nullptr) {
        aSyncContext = redisAsyncConnect(mServer->toChars(), mPort);
        mChannelListeners = createHashMap<String,HashSet<RedisSubscribeListener>>();
    }
}

void _RedisConnection::commandCallback(redisAsyncContext *redis_context,void *reply, void *privdata) {
    printf("onCommand!!!! \n");
    if (nullptr == reply || nullptr == privdata) {
        return ;
    }

    redisReply *redis_reply = reinterpret_cast<redisReply *>(reply);

    // 订阅接收到的消息是一个带三元素的数组
    if (redis_reply->type == REDIS_REPLY_ARRAY && redis_reply->elements == 3) {
        printf("Recieve message:%s %s %s\n",
        redis_reply->element[0]->str,
        redis_reply->element[1]->str,
        redis_reply->element[2]->str);
    } 
}

int _RedisConnection::subscribe(String channel,RedisSubscribeListener l) {
    _InitAsyncContext();
    printf("subscribe trace1 \n");
    bool isNeedSubscribe = false;
    {
        AutoLock l(mMutex);
        auto list = mChannelListeners->get(channel);
        if(list == nullptr) {
            list = createHashSet<RedisSubscribeListener>();
            mChannelListeners->put(channel,list);
            isNeedSubscribe = true;
        }
    }

    if(isNeedSubscribe) {
        printf("subscribe trace2,channe is %s \n",channel->toChars());
        int ret = redisAsyncCommand(aSyncContext,&commandCallback, this, "SUBSCRIBE %s",channel->toChars()); //订阅一个频道
        printf("ret is %d \n",ret);
        if (REDIS_ERR == ret) {
            LOG(ERROR)<< "subscribe failed!!!";
            return -1;
        } 
    }

    return 0;
}

int _RedisConnection::desubscribe(String channel,RedisSubscribeListener l) {
    return 0;
}

//https://blog.csdn.net/educast/article/details/37698809

}