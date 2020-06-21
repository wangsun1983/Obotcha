#include "Enviroment.hpp"
#include "AutoLock.hpp"
#include "ValueNotFoundException.hpp"

namespace obotcha {

Enviroment _Enviroment::mInstance = nullptr;

Mutex _Enviroment::mMutex = createMutex("EnviromentMutex");

String const _Enviroment::gHttpBufferSize = "env.http.buffer.size";
int const _Enviroment::DefaultHttpBufferSize = 512*1024;
    
String const _Enviroment::gWebSocketBufferSize = "env.ws.buffer.size";
int const _Enviroment::DefaultWebSocketBufferSize = 512*1024;

String const _Enviroment::gWebSocketFrameSize = "env.ws.frame.size";
int const _Enviroment::DefaultWebSocketFrameSize = 64*1024;

String const _Enviroment::gLocalSocketServerRcvBufferSize = "env.ls.server.rcv.size";
int const _Enviroment::DefaultLocalSocketServerRcvBufferSize = 64*1024;

String const _Enviroment::gLocalSocketServerClientNums = "env.ls.server.client.nums";
int const _Enviroment::DefaultLocalSocketServerClientNums = 64*1024;

String const _Enviroment::gTcpServerEpollSize = "env.tcp.server.epoll.size";
int const _Enviroment::DefaultTcpServerEpollSize = 8*1024;

String const _Enviroment::gTcpServerRcvBuffSize = "env.tcp.server.rcv.buffer.size";
int const _Enviroment::DefaultTcpServerRcvBuffSize = 64*1024;

String const _Enviroment::gTcpServerClientNums = "env.tcp.server.client.nums";
int const _Enviroment::DefaultTcpServerClientNums = 64*1024;

String const _Enviroment::gLocalSocketServerEpollSize = "env.ls.server.epoll.size";
int const _Enviroment::DefaultLocalSocketServerEpollSize = 8*1024;

String const _Enviroment::gLocalSocketBufferSize = "env.ls.buffer.size";
int const _Enviroment::DefaultLocalSocketBufferSize = 64*1024;

String const _Enviroment::gLocalSocketClientEpollSize = "env.ls.client.epoll.size";
int const _Enviroment::DefaultLocalSocketClientEpollSize = 8*1024;

String const _Enviroment::gAsyncTcpClientEpollSize = "env.aynsc.tcp.client.epoll.size";
int const _Enviroment::DefaultAsyncTcpClientEpollSize = 8*1024;

String const _Enviroment::gAsyncTcpClientBufferSize = "env.async.tcp.client.buffer.size";
int const _Enviroment::DefaultAsyncTcpClientBufferSize = 64*1024;

String const _Enviroment::gUdpClientEpollSize = "env.udp.client.epoll.size";
int const _Enviroment::DefaultUdpClientEpollSize = 8*1024;

String const _Enviroment::gUdpClientBufferSize = "env.udp.client.buffer.size";
int const _Enviroment::DefaultUdpClientBufferSize = 64*1024;

String const _Enviroment::gUdpServerEpollSize = "env.udp.server.epoll.size";
int const _Enviroment::DefaultUdpServerEpollSize = 8*1024;

String const _Enviroment::gUdpServerBufferSize = "env.udp.server.buffer.size";
int const _Enviroment::DefaultUdpServerBufferSize = 64*1024;

String const _Enviroment::gHttpServerPort = "http.server.port";
int const _Enviroment::DefaultHttpServerPort = 80;

String const _Enviroment::gHttpServerSendFileBufferSize ="http.server.sendfile.buffer.size";
int const _Enviroment::DefaultHttpServerSendFileBufferSize = 1024*128;

String const _Enviroment::gHttpMultiPartDispositionSize = "http.part.disposition.size";
int const _Enviroment::DefaultHttpMultiPartDispositionSize = 1024;

String const _Enviroment::gHttpMultiPartContentTypeSize = "http.part.contenttype.size";;
int const _Enviroment::DefaultHttpMultiContentTypeSize = 1024;

String const _Enviroment::gHttpMultiPartContentSize = "http.part.content.size";
int const  _Enviroment::DefaultHttpMultiContentSize = 32*1024;

String const  _Enviroment::gHttpMultiPartFilePath = "http.part.file.path";
String const _Enviroment::DefaultMultiPartFilePath = "./tmp/";

String const _Enviroment::gHttpSslKeyPath = "https.ssl.key.path";
String const _Enviroment::DefaultHttpSslKeyPath = "";

String const _Enviroment::gHttpSslCertificatePath = "https.ssl.cert.path";
String const _Enviroment::DefaultHttpSslCertificatePath = "";

sp<_Enviroment> _Enviroment::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _Enviroment *p = new _Enviroment();
    mInstance.set_pointer(p);
    return mInstance;
}

_Enviroment::_Enviroment() {
    mProp = createProperties();
    
    mProp->set(gHttpBufferSize,st(String)::valueOf(DefaultHttpBufferSize));
    mProp->set(gWebSocketBufferSize,st(String)::valueOf(DefaultWebSocketBufferSize));
    mProp->set(gWebSocketFrameSize,st(String)::valueOf(DefaultWebSocketFrameSize));
    mProp->set(gLocalSocketServerRcvBufferSize,st(String)::valueOf(DefaultLocalSocketServerRcvBufferSize));
    mProp->set(gLocalSocketServerClientNums,st(String)::valueOf(DefaultLocalSocketServerClientNums));
    mProp->set(gTcpServerEpollSize,st(String)::valueOf(DefaultTcpServerEpollSize));
    mProp->set(gTcpServerRcvBuffSize,st(String)::valueOf(DefaultTcpServerRcvBuffSize));
    mProp->set(gTcpServerClientNums,st(String)::valueOf(DefaultTcpServerClientNums));
    mProp->set(gLocalSocketServerEpollSize,st(String)::valueOf(DefaultLocalSocketServerEpollSize));
    mProp->set(gLocalSocketBufferSize,st(String)::valueOf(DefaultLocalSocketBufferSize));
    mProp->set(gLocalSocketClientEpollSize,st(String)::valueOf(DefaultLocalSocketClientEpollSize));
    mProp->set(gAsyncTcpClientEpollSize,st(String)::valueOf(DefaultAsyncTcpClientEpollSize));
    mProp->set(gAsyncTcpClientBufferSize,st(String)::valueOf(DefaultAsyncTcpClientBufferSize));
    mProp->set(gUdpClientEpollSize,st(String)::valueOf(DefaultUdpClientEpollSize));
    mProp->set(gUdpClientBufferSize,st(String)::valueOf(DefaultUdpClientBufferSize));
    mProp->set(gUdpServerEpollSize,st(String)::valueOf(DefaultUdpServerEpollSize));
    mProp->set(gUdpServerBufferSize,st(String)::valueOf(DefaultUdpServerBufferSize));
    mProp->set(gHttpServerPort,st(String)::valueOf(DefaultHttpServerPort));
    mProp->set(gHttpServerSendFileBufferSize,st(String)::valueOf(DefaultHttpServerSendFileBufferSize));
    mProp->set(gHttpMultiPartDispositionSize,st(String)::valueOf(DefaultHttpMultiPartDispositionSize));
    mProp->set(gHttpMultiPartContentTypeSize,st(String)::valueOf(DefaultHttpMultiContentTypeSize));
    mProp->set(gHttpMultiPartContentSize,st(String)::valueOf(DefaultHttpMultiContentSize));
    mProp->set(gHttpMultiPartFilePath,DefaultMultiPartFilePath);
    mProp->set(gHttpSslKeyPath,DefaultHttpSslKeyPath);
    mProp->set(gHttpSslCertificatePath,DefaultHttpSslCertificatePath);
}

void _Enviroment::set(String tag,String v) {
    mProp->set(tag,v);
}

int _Enviroment::getInt(String v,int defaultvalue) {
    String value = mProp->get(v);
    if(value != nullptr) {
        return value->toBasicInt();
    }

    return defaultvalue;
}

bool _Enviroment::getBoolean(String v,bool defaultvalue){
    String value = mProp->get(v);
    if(value != nullptr) {
        return value->toBasicBool();
    }

    return defaultvalue;
}

String _Enviroment::get(String v) {
    return mProp->get(v);;
}

String _Enviroment::get(String v,String defaultvalue) {
    String value = mProp->get(v);
    if(value == nullptr) {
        return defaultvalue;
    }

    return value;
}

}
