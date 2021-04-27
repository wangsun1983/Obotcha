#ifndef __OBOTCHA_ENVIROMENT_HPP__
#define __OBOTCHA_ENVIROMENT_HPP__

#include <mutex>
#include <thread>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Properties.hpp"
#include "Mutex.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Enviroment) {

public:
    static Enviroment getInstance();

    void set(String,String);

    int getInt(String,int defaultvalue);

    bool getBoolean(String,bool defaultvalue);

    String get(String);

    String get(String,String defaultvalue);

    static const String gHttpBufferSize;
    static const int DefaultHttpBufferSize;

    static const String gHttpServerThreadsNum;
    static const int DefaultgHttpServerThreadsNum;
    
    static const String gWebSocketBufferSize;
    static const int DefaultWebSocketBufferSize;

    static const String gWebSocketRcvThreadsNum;
    static const int DefaultWebSocketRcvThreadsNum;

    static const String gWebSocketFrameSize;
    static const int DefaultWebSocketFrameSize;

    static const String gLocalSocketServerRcvBufferSize;
    static const int DefaultLocalSocketServerRcvBufferSize;

    static const String gLocalSocketServerClientNums;
    static const int DefaultLocalSocketServerClientNums;

    static const String gTcpServerEpollSize;
    static const int DefaultTcpServerEpollSize;

    static const String gTcpServerRcvBuffSize;
    static const int DefaultTcpServerRcvBuffSize;

    static const String gTcpServerClientNums;
    static const int DefaultTcpServerClientNums;

    static const String gLocalSocketServerEpollSize;
    static const int DefaultLocalSocketServerEpollSize;

    static const String gLocalSocketBufferSize;
    static const int DefaultLocalSocketBufferSize;

    static const String gLocalSocketClientEpollSize;
    static const int DefaultLocalSocketClientEpollSize;

    static const String gAsyncTcpClientEpollSize;
    static const int DefaultAsyncTcpClientEpollSize;

    static const String gAsyncTcpClientBufferSize;
    static const int DefaultAsyncTcpClientBufferSize;

    static const String gUdpClientEpollSize;
    static const int DefaultUdpClientEpollSize;

    static const String gUdpClientBufferSize;
    static const int DefaultUdpClientBufferSize;

    static const String gUdpServerEpollSize;
    static const int DefaultUdpServerEpollSize;

    static const String gUdpServerBufferSize;
    static const int DefaultUdpServerBufferSize;

    static const String gHttpServerPort;
    static const int DefaultHttpServerPort;

    static const String gHttpServerSendFileBufferSize;
    static const int DefaultHttpServerSendFileBufferSize;

    static const String gHttpMultiPartDispositionSize;
    static const int DefaultHttpMultiPartDispositionSize;

    static const String gHttpMultiPartContentTypeSize;
    static const int DefaultHttpMultiContentTypeSize;

    static const String gHttpMultiPartContentSize;
    static const int DefaultHttpMultiContentSize;

    static const String gHttpMultiPartFilePath;
    static const String DefaultMultiPartFilePath;

    static const String gHttpSslKeyPath;
    static const String DefaultHttpSslKeyPath;

    static const String gHttpSslCertificatePath;
    static const String DefaultHttpSslCertificatePath;    

private:
    _Enviroment();
    
    static std::once_flag s_flag;
    static Enviroment mInstance;
   
    Properties mProp;
};

}
#endif