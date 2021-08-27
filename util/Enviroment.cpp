#include "Enviroment.hpp"
#include "AutoLock.hpp"
#include "System.hpp"

namespace obotcha {

std::once_flag _Enviroment::s_flag;
Enviroment _Enviroment::mInstance;

String const _Enviroment::gHttpBufferSize = "env.http.buffer.size";
int const _Enviroment::DefaultHttpBufferSize = 512*1024;

String const _Enviroment::gHttpServerThreadsNum = "env.http.server.thread.num";
int const _Enviroment::DefaultgHttpServerThreadsNum = st(System)::availableProcessors();
    
String const _Enviroment::gWebSocketBufferSize = "env.ws.buffer.size";
int const _Enviroment::DefaultWebSocketBufferSize = 512*1024;

String const _Enviroment::gWebSocketRcvThreadsNum = "env.ws.threads.num";
int const _Enviroment::DefaultWebSocketRcvThreadsNum = st(System)::availableProcessors();

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
    std::call_once(s_flag, [&]() {
        _Enviroment *p = new _Enviroment();
        p->mInstance.set_pointer(p);
    });

    return mInstance;
}

_Enviroment::_Enviroment() {
    mProp = createHashMap<String,String>();
    
    mProp->put(gHttpBufferSize,st(String)::valueOf(DefaultHttpBufferSize));
    mProp->put(gHttpServerThreadsNum,st(String)::valueOf(DefaultgHttpServerThreadsNum));
    mProp->put(gWebSocketBufferSize,st(String)::valueOf(DefaultWebSocketBufferSize));
    mProp->put(gWebSocketBufferSize,st(String)::valueOf(DefaultWebSocketRcvThreadsNum));
    mProp->put(gWebSocketFrameSize,st(String)::valueOf(DefaultWebSocketFrameSize));
    mProp->put(gLocalSocketServerRcvBufferSize,st(String)::valueOf(DefaultLocalSocketServerRcvBufferSize));
    mProp->put(gLocalSocketServerClientNums,st(String)::valueOf(DefaultLocalSocketServerClientNums));
    mProp->put(gTcpServerEpollSize,st(String)::valueOf(DefaultTcpServerEpollSize));
    mProp->put(gTcpServerRcvBuffSize,st(String)::valueOf(DefaultTcpServerRcvBuffSize));
    mProp->put(gTcpServerClientNums,st(String)::valueOf(DefaultTcpServerClientNums));
    mProp->put(gLocalSocketServerEpollSize,st(String)::valueOf(DefaultLocalSocketServerEpollSize));
    mProp->put(gLocalSocketBufferSize,st(String)::valueOf(DefaultLocalSocketBufferSize));
    mProp->put(gLocalSocketClientEpollSize,st(String)::valueOf(DefaultLocalSocketClientEpollSize));
    mProp->put(gAsyncTcpClientEpollSize,st(String)::valueOf(DefaultAsyncTcpClientEpollSize));
    mProp->put(gAsyncTcpClientBufferSize,st(String)::valueOf(DefaultAsyncTcpClientBufferSize));
    mProp->put(gUdpClientEpollSize,st(String)::valueOf(DefaultUdpClientEpollSize));
    mProp->put(gUdpClientBufferSize,st(String)::valueOf(DefaultUdpClientBufferSize));
    mProp->put(gUdpServerEpollSize,st(String)::valueOf(DefaultUdpServerEpollSize));
    mProp->put(gUdpServerBufferSize,st(String)::valueOf(DefaultUdpServerBufferSize));
    mProp->put(gHttpServerPort,st(String)::valueOf(DefaultHttpServerPort));
    mProp->put(gHttpServerSendFileBufferSize,st(String)::valueOf(DefaultHttpServerSendFileBufferSize));
    mProp->put(gHttpMultiPartDispositionSize,st(String)::valueOf(DefaultHttpMultiPartDispositionSize));
    mProp->put(gHttpMultiPartContentTypeSize,st(String)::valueOf(DefaultHttpMultiContentTypeSize));
    mProp->put(gHttpMultiPartContentSize,st(String)::valueOf(DefaultHttpMultiContentSize));
    mProp->put(gHttpMultiPartFilePath,DefaultMultiPartFilePath);
    mProp->put(gHttpSslKeyPath,DefaultHttpSslKeyPath);
    mProp->put(gHttpSslCertificatePath,DefaultHttpSslCertificatePath);
}

void _Enviroment::set(String tag,String v) {
    mProp->put(tag,v);
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
