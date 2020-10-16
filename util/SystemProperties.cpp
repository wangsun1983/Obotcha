#include "SystemProperties.hpp"
#include "Error.hpp"
#include "Log.hpp"

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
    cc->release();
    return result;
}

String _SystemProperties::get(String key) {
    struct _SystemPropertiesData data;
    data.command = GetCommand;
    if(key->size() >= DataSize) {
        return nullptr;
    }
    memcpy(data.key,key->toChars(),key->size());
    ByteArray packet = createByteArray((byte*)&data,sizeof(struct _SystemPropertiesData));

    LocalSocketClient cc = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),nullptr);
    cc->doConnect();
    int result = cc->doSend(packet);
    if(result > 0) {
        ByteArray recvData = cc->doReceive();
        struct _SystemPropertiesData *response = (struct _SystemPropertiesData *)recvData->toValue();
        cc->release();
        if(response == nullptr) {
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
        LOG(ERROR)<<"pack is nullptr";
        return;
    }

    switch(response->command) {
        case GetCommand: {
            String key = createString(response->key);
            String value = nullptr;
            {
                AutoLock l(mDataMutex);
                value = mValues->get(key);
                memcpy(response->value,value->toChars(),value->size());
                response->value[value->size()] = 0;
                response->command = RespCommand;
                write(fd,response,sizeof(struct _SystemPropertiesData));
            }
        }
        break;

        case SetCommand: {
            String key = createString(response->key);
            String value = createString(response->value);
            AutoLock l(mDataMutex);
            mValues->put(key,value);

            //we should notify all listener
            response->command = UpdateNotifyCommand;

            HashSet<int> ll = mListeners->get(key);
            if(ll != nullptr) {
                HashSetIterator<int>iterator = ll->getIterator();
                std::vector<int> fails;

                while(iterator->hasValue()) {
                    int _fd = iterator->getValue();
                    int ret = write(_fd,response,sizeof(struct _SystemPropertiesData));
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
            String key = createString(response->key);
            HashSet<int> ll = mListeners->get(key);
            if(ll == nullptr) {
                ll = createHashSet<int>();
                mListeners->put(key,ll);
            }
            ll->add(fd);
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

void _SystemProperties::onDataReceived(SocketResponser r,ByteArray pack) {
    if(mClient != nullptr && mClient->getSock() == r->getFd()) {
        onClientCommand(r->getFd(),r->getIp(),r->getPort(),pack);
    } else {
        onServerCommand(r->getFd(),r->getIp(),r->getPort(),pack);
    }
}

void _SystemProperties::runAsServer() {
    mServer = createLocalSocketServer(path,
                                    AutoClone(this),
                                    st(LocalSocketServer)::DefaultLocalClientNums,
                                    sizeof(struct _SystemPropertiesData));

    mListeners = createHashMap<String,HashSet<int>>();

    if(mServer->tryStart() == 0){
        mDataMutex = createMutex("sysprop");
        mValues = createHashMap<String,String>();
    }
}

void _SystemProperties::registListener(String key,SystemPropertiesListener l) {
    if(mClient == nullptr) {
        mClient = createLocalSocketClient(path,1000,sizeof(struct _SystemPropertiesData),AutoClone(this));
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

void _SystemProperties::onDisconnect(SocketResponser r) {
    close(r->getFd());
    MapIterator<String,HashSet<int>> iterator = mListeners->getIterator();
    while(iterator->hasValue()) {
        HashSet<int> l = iterator->getValue();
        if(l != nullptr) {
            l->remove(r->getFd());
            return;        
        }

        iterator->next();
    }
}

void _SystemProperties::onConnect(SocketResponser r) {
   
}

void _SystemProperties::onTimeout() {

}



}