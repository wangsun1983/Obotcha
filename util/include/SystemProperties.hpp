#ifndef __OBOTCHA_SYSTEM_PROPERTIES_HPP__
#define __OBOTCHA_SYSTEM_PROPERTIES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "File.hpp"
#include "LocalSocketServer.hpp"
#include "LocalSocketClient.hpp"
#include "HashSet.hpp"

namespace obotcha {

class _SystemProperties;

DECLARE_SIMPLE_CLASS(SystemPropertiesListener) {
public:
    virtual void onDataChanged(String key,String value) = 0;
};


DECLARE_SIMPLE_CLASS(SystemProperties) IMPLEMENTS(SocketListener){

public:
    static sp<_SystemProperties> getInstance();

    int set(String key,String value);

    String get(String key);

    void registListener(String,SystemPropertiesListener);
    
    void unregistListener(String,SystemPropertiesListener);

    void runAsServer();

    static const int DataSize = 513;

private:
    struct _SystemPropertiesData {
        int command;
        char key[_SystemProperties::DataSize];
        char value[_SystemProperties::DataSize];    
    };
    
    static const String path;

    static const int GetCommand = 0;
    static const int SetCommand = 1;
    static const int ListenCommand = 2;
    static const int UnListenCommand = 3;
    static const int RespCommand = 4;
    static const int UpdateNotifyCommand = 5;

    static Mutex initMutex;
    static sp<_SystemProperties> mInstance;

    void onDataReceived(SocketResponser r,ByteArray pack);

    void onDisconnect(SocketResponser r);

    void onConnect(SocketResponser r);

    void onTimeout();

    _SystemProperties();

    void onServerCommand(int fd,String ip,int port,ByteArray pack);
    void onClientCommand(int fd,String ip,int port,ByteArray pack);
    
    //client
    HashMap<String,ArrayList<SystemPropertiesListener>> mClientListeners;

    //servers
    Mutex mDataMutex;
    
    HashMap<String,String> mValues;

    HashMap<String,HashSet<int>> mListeners;

    LocalSocketServer mServer;

    LocalSocketClient mClient;

    
};

}
#endif