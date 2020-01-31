#ifndef __ENVIROMENT_HPP__
#define __ENVIROMENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Properties.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Enviroment) {

public:
    static Enviroment getInstance();

    void set(String,String);

    int getInt(String);

    int getInt(String,int defaultvalue);

    bool getBoolean(String);

    int getBoolean(String,bool defaultvalue);

    String get(String);

    String get(String,String defaultvalue);

    static const String gHttpBufferSize;
    static const int DefaultHttpBufferSize = 512*1024;
    
    static const String gWebSocketBufferSize;
    static const int DefaultWebSocketBufferSize = 512*1024;

    static const String gWebSocketFrameSize;
    static const int DefaultWebSocketFrameSize = 64*1024;

    static const String gLocalSocketServerRcvBufferSize;
    static const int DefaultLocalSocketServerRcvBufferSize = 64*1024;

    static const String gLocalSocketServerClientNums;
    static const int DefaultLocalSocketServerClientNums = 64*1024;

    static const String gTcpServerEpollSize;
    static const int DefaultTcpServerEpollSize = 8*1024;

    static const String gTcpServerRcvBuffSize;
    static const int DefaultTcpServerRcvBuffSize = 64*1024;

    static const String gTcpServerClientNums;
    static const int DefaultTcpServerClientNums = 64*1024;

    static const String gLocalSocketServerEpollSize;
    static const int DefaultLocalSocketServerEpollSize = 8*1024;

    static const String gLocalSocketBufferSize;
    static const int DefaultLocalSocketBufferSize = 64*1024;

    static const String gLocalSocketClientEpollSize;
    static const int DefaultLocalSocketClientEpollSize = 8*1024;

    static const String gAsyncTcpClientEpollSize;
    static const int DefaultAsyncTcpClientEpollSize = 8*1024;

    static const String gAsyncTcpClientBufferSize;
    static const int DefaultAsyncTcpClientBufferSize = 64*1024;

    static const String gUdpClientEpollSize;
    static const int DefaultUdpClientEpollSize = 8*1024;

    static const String gUdpClientBufferSize;
    static const int DefaultUdpClientBufferSize = 64*1024;

    static const String gUdpServerEpollSize;
    static const int DefaultUdpServerEpollSize = 8*1024;

    static const String gUdpServerBufferSize;
    static const int DefaultUdpServerBufferSize = 64*1024;

    static const String gHttpServerPort;
    static const int DefaultHttpServerPort = 80;

private:
    _Enviroment();

    static Enviroment mInstance;
   
    static Mutex mMutex;
   
    Properties mProp;
};

}
#endif