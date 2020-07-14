#ifndef __OBOTCHA_SYSTEM_PROPERTIES_HPP__
#define __OBOTCHA_SYSTEM_PROPERTIES_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"
#include "File.hpp"
#include "LocalSocketServer.hpp"
#include "LocalSocketClient.hpp"

namespace obotcha {

class _SystemProperties;



DECLARE_SIMPLE_CLASS(SystemProperties) IMPLEMENTS(SocketListener){

public:
    static sp<_SystemProperties> getInstance();

    int set(String key,String value);

    String get(String key);

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
    static const int RespCommand = 2;

    static Mutex initMutex;
    static sp<_SystemProperties> mInstance;

    void onAccept(int fd,String ip,int port,ByteArray pack);

    void onDisconnect(int fd);

    void onConnect(int fd,String ip,int port);

    void onConnect(int fd,String domain);

    void onTimeout();

    _SystemProperties();
    
    Mutex mDataMutex;

    HashMap<String,String> mValues;

    LocalSocketServer mServer;

    LocalSocketClient mClient;

    
};

}
#endif