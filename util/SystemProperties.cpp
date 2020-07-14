#include "SystemProperties.hpp"
#include "Error.hpp"

namespace obotcha {

const String _SystemProperties::path = createString("sysprops");
Mutex _SystemProperties::initMutex = createMutex("sysprop init");
sp<_SystemProperties> _SystemProperties::mInstance = nullptr;

sp<_SystemProperties> _SystemProperties::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(initMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }
    
    _SystemProperties *p = new _SystemProperties();
    mInstance.set_pointer(p);
    return mInstance;
}

_SystemProperties::_SystemProperties() {
    //domain,SocketListener l,int clients = gDefaultLocalClientNums, int recvsize=gDefaultLocalRcvBuffSize
    SocketListener l;
    l.set_pointer(this);
    mServer = createLocalSocketServer(path,l,gDefaultLocalClientNums,sizeof(struct _SystemPropertiesData));
    if(mServer->tryStart() == 0){
        mDataMutex = createMutex("sysprop");
        mValues = createHashMap<String,String>();
    }

    //(String domain,int recv_time,int buff_size = 1024,SocketListener l = nullptr
    mClient = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),nullptr);
    mClient->doConnect();
}

int _SystemProperties::set(String key,String value) {
    struct _SystemPropertiesData data;
    data.command = SetCommand;

    if(key->size() >= DataSize || value->size() >= DataSize) {
        return -InvalidParam;
    }

    memcpy(data.key,key->toChars(),key->size());
    memcpy(data.value,value->toChars(),value->size());

    ByteArray packet = createByteArray((byte*)&data,sizeof(struct _SystemPropertiesData));

    return mClient->doSend(packet);
}

String _SystemProperties::get(String key) {
    struct _SystemPropertiesData data;
    data.command = GetCommand;
    if(key->size() >= DataSize) {
        return nullptr;
    }
    printf("start get \n");
    memcpy(data.key,key->toChars(),key->size());
    ByteArray packet = createByteArray((byte*)&data,sizeof(struct _SystemPropertiesData));
    int result = mClient->doSend(packet);
    printf("start get result is %d\n",result);
    if(result > 0) {
        ByteArray recvData = mClient->doReceive();
        struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)recvData->toValue();
        if(response == nullptr) {
            printf("start get result is nullptr\n");
            return nullptr;
        }
        return createString(response->value);
    }

    return nullptr;
}

void _SystemProperties::onAccept(int fd,String ip,int port,ByteArray pack) {
    struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)pack->toValue();
    if(pack == nullptr) {
        //TODO
    }

    switch(response->command) {
        case GetCommand: {
            printf("on GetCommand ,key is %s\n",response->key);
            String key = createString(response->key);
            String value = nullptr;
            {
                AutoLock l(mDataMutex);
                value = mValues->get(key);
                printf("onGetCommand Value is %s \n",value->toChars());
                memcpy(response->value,value->toChars(),value->size());
                response->value[value->size()] = 0;
                response->command = RespCommand;
                write(fd,response,sizeof(struct _SystemPropertiesData));
            }
        }
        break;

        case SetCommand: {
            printf("on setCommand ,key is %s\n",response->key);
            printf("on setCommand ,value is %s\n",response->value);
            String key = createString(response->key);
            String value = createString(response->value);
            AutoLock l(mDataMutex);
            mValues->put(key,value);
        }
        break;
    }
    
}

void _SystemProperties::onDisconnect(int fd) {

}

void _SystemProperties::onConnect(int fd,String ip,int port) {

}

void _SystemProperties::onConnect(int fd,String domain) {

}

void _SystemProperties::onTimeout() {

}



}