#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "RedisClient.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"
#include "ArrayList.hpp"

namespace obotcha {
//http://doc.redisfans.com/

int _RedisClient::connect(String server,int port,long millseconds) {
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
}

int _RedisClient::set(String key,String value) {
    redisReply *reply = (redisReply *)redisCommand(mContext,"SET %b %b", key->toChars(),key->size(),value->toChars(),value->size());
    if(reply == nullptr) {
        return -1;
    }

    freeReplyObject(reply);
    return 0;
}

int _RedisClient::set(String key,int value) {
    redisReply *reply = (redisReply *)redisCommand(mContext,"SET %b %d", key->toChars(),key->size(),value);
    if(reply == nullptr) {
        return -1;
    }

    freeReplyObject(reply);
    return 0;
}

String _RedisClient::getValue(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"GET %s");
    if(reply == nullptr || reply->str == nullptr) {
        return nullptr;
    }
    String value = createString(reply->str);
    freeReplyObject(reply);
    return value;
}

int _RedisClient::incValue(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"INCR %s",key->toChars());
    int value = reply->integer;
    freeReplyObject(reply);
    return value;
}

int _RedisClient::decValue(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"DECR %s",key->toChars());
    int value = reply->integer;
    freeReplyObject(reply);
    return value;
}

int _RedisClient::delList(String key) {
    redisReply * reply = (redisReply *)redisCommand(mContext,"DEL %s",key->toChars());
    if(reply == nullptr) {
        return -1;
    }
    freeReplyObject(reply);
    return 0;
}

int _RedisClient::set(String key,ArrayList<String> list){
    ListIterator<String> iterator = list->getIterator();
    while(iterator->hasValue()) {
        redisReply * reply = (redisReply *)redisCommand(mContext,"LPUSH %s element-%s",key->toChars(),iterator->getValue()->toChars());
        freeReplyObject(reply);
        iterator->next();
    }
    return 0;
}

}