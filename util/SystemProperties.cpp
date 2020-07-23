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
    mListeners = createHashMap<String,HashSet<int>>();

    if(mServer->tryStart() == 0){
        mDataMutex = createMutex("sysprop");
        mValues = createHashMap<String,String>();
    }

    //(String domain,int recv_time,int buff_size = 1024,SocketListener l = nullptr
    //mClient = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),nullptr);
    //mClient->doConnect();
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
    LocalSocketClient cc = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),nullptr);
    cc->doConnect();
    int result = cc->doSend(packet);
    printf("set result is %d \n",result);
    cc->release();
    return result;
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

    LocalSocketClient cc = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),nullptr);
    cc->doConnect();
    int result = cc->doSend(packet);
    printf("start get result is %d\n",result);
    if(result > 0) {
        ByteArray recvData = cc->doReceive();
        struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)recvData->toValue();
        cc->release();
        if(response == nullptr) {
            printf("start get result is nullptr\n");
            return nullptr;
        }
        return createString(response->value);
    }
    
    cc->release();
    return nullptr;
}

void _SystemProperties::onServerCommand(int fd,String ip,int port,ByteArray pack) {
    struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)pack->toValue();
    if(pack == nullptr) {
        //TODO
        printf("pack is nullptr \n");
        return;
    }

    printf("response command is %d \n",response->command);

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

            //we should notify all listener
            response->command = UpdateNotifyCommand;

            HashSet<int> ll = mListeners->get(key);
            if(ll != nullptr) {
                printf("set command ll is not nullptr,ll size is %d \n",ll->size());
                HashSetIterator<int>iterator = ll->getIterator();
                std::vector<int> fails;

                while(iterator->hasValue()) {
                    int _fd = iterator->getValue();
                    printf("write fd is %d \n",fd);
                    int ret = write(_fd,response,sizeof(struct _SystemPropertiesData));
                    printf("write fd is %d,ret is %d \n",_fd,ret);
                    if(ret <= 0) {
                        fails.push_back(_fd);
                        continue;
                    }
                    iterator->next();
                }
            }
        }
        break;

        case ListenCommand: {
            printf("do listen command \n");
            String key = createString(response->key);
            HashSet<int> ll = mListeners->get(key);
            if(ll == nullptr) {
                ll = createHashSet<int>();
                mListeners->put(key,ll);
            }
            ll->add(fd);
            printf("do listen ll size is %d \n",ll->size());
        }
        break;

        case UnListenCommand: {
            String key = createString(response->key);
            HashSet<int> ll = mListeners->get(key);
            HashSetIterator<int> iterator = ll->getIterator();
            while(iterator->hasValue()) {
                if(iterator->getValue() == fd) {
                    ll->remove(fd);
                    return;
                }
            }
        }
        break;
    }
}

void _SystemProperties::onClientCommand(int fd,String ip,int port,ByteArray pack) {
    struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)pack->toValue();
    if(pack == nullptr) {
        //TODO
        return;
    }

    switch(response->command) {
        case UpdateNotifyCommand:
            String key = createString(response->key);
            String value = createString(response->value);
            ArrayList<SystemPropertiesListener> ll = mClientListeners->get(key);
            ListIterator<SystemPropertiesListener> iterator = ll->getIterator();
            while(iterator->hasValue()) {
                SystemPropertiesListener l = iterator->getValue();
                l->onDataChanged(key,value);
                iterator->next();
            }
        break;
    }
}

void _SystemProperties::onAccept(int fd,String ip,int port,ByteArray pack) {
    printf("onAccept fd is %d \n",fd);
    if(mClient != nullptr && mClient->getSock() == fd) {
        printf("mClient fd is %d \n",mClient->getSock());
        onClientCommand(fd,ip,port,pack);
    } else {
        printf("mServer fd is %d \n",mServer->getSock());
        onServerCommand(fd,ip,port,pack);
    }
}

void _SystemProperties::registListener(String key,SystemPropertiesListener l) {
    if(mClient == nullptr) {
        SocketListener listener;
        listener.set_pointer(this);
        mClient = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),listener);
        mClient->doConnect();
    }

    if(mClientListeners == nullptr) {
        mClientListeners = createHashMap<String,ArrayList<SystemPropertiesListener>>();
    }

    ArrayList<SystemPropertiesListener> ll = mClientListeners->get(key);
    if(ll == nullptr) {
        ll = createArrayList<SystemPropertiesListener>();
        mClientListeners->put(key,ll);
    }

    ll->add(l);

    struct _SystemPropertiesData data;
    data.command = ListenCommand;
    memcpy(data.key,key->toChars(),key->size());
    ByteArray packet = createByteArray((byte*)&data,sizeof(struct _SystemPropertiesData));
    mClient->doSend(packet);
    //write(fd,response,sizeof(struct _SystemPropertiesData));
}
    
void _SystemProperties::unregistListener(String key,SystemPropertiesListener l) {
    if(mClientListeners == nullptr) {
        return;
    }

    ArrayList<SystemPropertiesListener> ll = mClientListeners->get(key);
    if(ll == nullptr) {
        return;
    }

    //send command
    struct _SystemPropertiesData data;
    data.command = UnListenCommand;
    memcpy(data.key,key->toChars(),key->size());
    ByteArray packet = createByteArray((byte*)&data,sizeof(struct _SystemPropertiesData));
    mClient->doSend(packet);

    ListIterator<SystemPropertiesListener>iterator = ll->getIterator();
    while(iterator->hasValue()) {
        if(iterator->getValue() == l) {
            iterator->remove();
            continue;
        }
        iterator->next();
    }
}

void _SystemProperties::onDisconnect(int fd) {
    close(fd);
}

void _SystemProperties::onConnect(int fd,String ip,int port) {
   
}

void _SystemProperties::onConnect(int fd,String domain) {

}

void _SystemProperties::onTimeout() {

}



}