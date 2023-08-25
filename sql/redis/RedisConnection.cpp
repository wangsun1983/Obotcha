#include "RedisConnection.hpp"
#include "Log.hpp"
#include "InitializeException.hpp"
#include "ArrayList.hpp"
#include "AutoLock.hpp"
#include "Log.hpp"

namespace obotcha {

//http://doc.redisfans.com/
_RedisConnection::_RedisConnection() {
    mMutex = createMutex();
    aSyncContext = nullptr;
    mContext = nullptr;
    isInLooper = false;
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
        Trigger(InitializeException,"redis connect fail")
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
    ArrayListIterator<String> iterator = list->getIterator();
    while(iterator->hasValue()) {
        redisReply * reply = (redisReply *)redisCommand(mContext,"LPUSH %s element-%s",key->toChars(),iterator->getValue()->toChars());
        freeReplyObject(reply);
        iterator->next();
    }
    return 0;
}

void _RedisConnection::_InitAsyncContext() {
    AutoLock l(mMutex);
    if(aSyncContext == nullptr) {
        aSyncContext = redisAsyncConnect(mServer->toChars(), mPort);
        mChannelListeners = createHashMap<String,HashSet<RedisSubscribeListener>>();

        aSyncContext->ev.data = this;
        aSyncContext->ev.addRead = _RedisAddRead;
        aSyncContext->ev.delRead = _RedisDelRead;
        aSyncContext->ev.addWrite = _RedisAddWrite;
        aSyncContext->ev.delWrite = _RedisDelWrite;
        aSyncContext->ev.cleanup = _RedisCleanup;

        mEpoll = createEPollObserver();
        mEpoll->addObserver(aSyncContext->c.fd,EPOLLIN|EPOLLET,AutoClone(this));
    
    }
}

void _RedisConnection::_RedisAddRead(void * c) {
    redisAsyncContext *ctx = (redisAsyncContext *)c;
    //TODO? need test check
    redisAsyncHandleRead(ctx);
}

void _RedisConnection::_RedisDelRead(void * c) {
    //printf("_RedisDelRead \n");
}

void _RedisConnection::_RedisAddWrite(void * c) {
    //printf("_RedisAddWrite \n");
    _RedisConnection *connection = (_RedisConnection *)c;
    redisAsyncHandleWrite(connection->aSyncContext);
}

void _RedisConnection::_RedisDelWrite(void * c) {
    //printf("_RedisDelWrite \n");
}

void _RedisConnection::_RedisCleanup(void * c) {
    //printf("_RedisCleanup \n");
}


void _RedisConnection::_CommandCallback(redisAsyncContext *redis_context,void *reply, void *privdata) {
    if (nullptr == reply || nullptr == privdata) {
        return ;
    }

    _RedisConnection *c = (_RedisConnection *)privdata;
    redisReply *redis_reply = reinterpret_cast<redisReply *>(reply);

    if (redis_reply->type == REDIS_REPLY_ARRAY && redis_reply->elements == 3) {
        String type = createString(redis_reply->element[0]->str);
        int event = Message;

        if(type->equalsIgnoreCase("subscribe")) {
            event = RedisEvent::Subscribe;
        } else if(type->equalsIgnoreCase("message")) {
            event = RedisEvent::Message;
        } else if(type->equalsIgnoreCase("unsubscribe")) {
            event = RedisEvent::UnSubscribe;
        } else {
            LOG(ERROR)<<"unsupport redis response :"<<type->toChars();
        }
        
        String key = createString(redis_reply->element[1]->str);
        String value = nullptr;
        if(redis_reply->element[2]->str != nullptr) {
            value = createString(redis_reply->element[2]->str);
        }
        c->_onEventTrigger(event,key,value);
    } 
}

void _RedisConnection::_onEventTrigger(int event,String key,String value) {
    AutoLock l(mMutex);
    auto set = mChannelListeners->get(key);
    auto iterator = set->getIterator();
    isInLooper = true;
    while(iterator->hasValue()) {
        RedisSubscribeListener l = iterator->getValue();
        l->onEvent(event,key,value);
        iterator->next();
    }
    isInLooper = false;
}

int _RedisConnection::subscribe(String channel,_RedisSubscribeLambda l) {
    auto listener = createLambdaRedisSubscribeListener(l);
    return subscribe(channel,listener);
}

int _RedisConnection::subscribe(String channel,RedisSubscribeListener l) {
    _InitAsyncContext();
    if(isInLooper) {
        LOG(ERROR)<<"can not subscribe channel in RedisSubscribeListener";
        return 0;
    }

    bool isNeedSubscribe = false;
    {
        AutoLock ll(mMutex);
        HashSet<RedisSubscribeListener> list = mChannelListeners->get(channel);
        if(list == nullptr) {
            list = createHashSet<RedisSubscribeListener>();
            mChannelListeners->put(channel,list);
            isNeedSubscribe = true;
        }

        list->add(l);
    }
    
    if(isNeedSubscribe) {
        int ret = redisAsyncCommand(aSyncContext,&_CommandCallback, this, "SUBSCRIBE %s",channel->toChars());
        if (REDIS_ERR == ret) {
            LOG(ERROR)<< "subscribe failed!!!";
            return -1;
        } 
    }

    return 0;
}

st(IO)::Epoll::Result _RedisConnection::onEvent(int fd, uint32_t events) {
    redisAsyncRead(aSyncContext);
    return st(IO)::Epoll::Result::Ok;
}

int _RedisConnection::unsubscribe(String channel,RedisSubscribeListener l) {
    AutoLock ll(mMutex);
    if(isInLooper) {
        LOG(ERROR)<<"can not subscribe channel in RedisSubscribeListener";
        return 0;
    }

    HashSet<RedisSubscribeListener> list = mChannelListeners->get(channel);
    list->remove(l);
    if(list->size() == 0) {
        int ret = redisAsyncCommand(aSyncContext,&_CommandCallback, this, "UNSUBSCRIBE %s",channel->toChars());
        if (REDIS_ERR == ret) {
            LOG(ERROR)<< "subscribe failed!!!";
            return -1;
        } 
    }
    return 0;
}

int _RedisConnection::publish(String key,String value) {
    _InitAsyncContext();
    int ret = redisAsyncCommand(aSyncContext,&_CommandCallback, this, "PUBLISH %s %s",key->toChars(),value->toChars());
    if (REDIS_ERR == ret) {
        LOG(ERROR)<< "publish failed!!!";
        return -1;
    }

    return 0;
}

int _RedisConnection::close() {
    if(mEpoll != nullptr) {
        mEpoll->close();
        mEpoll = nullptr;
    }

    if(aSyncContext != nullptr) {
        redisAsyncFree(aSyncContext);
        aSyncContext = nullptr;
    }

    if(mContext != nullptr) {
        redisFree(mContext);
        mContext = nullptr;
    }

    return 0;
}

_RedisConnection::~_RedisConnection() {
    close();
}

}