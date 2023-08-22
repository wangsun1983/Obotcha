#include <mutex>

#include "Enviroment.hpp"
#include "System.hpp"

namespace obotcha {

Enviroment _Enviroment::mInstance = nullptr;

String const _Enviroment::gHttpBufferSize =
    createString("env.http.buffer.size");
int const _Enviroment::DefaultHttpBufferSize = 512 * 1024;

String const _Enviroment::gHttpServerThreadsNum =
    createString("env.http.server.thread.num");
int const _Enviroment::DefaultgHttpServerThreadsNum =
    st(System)::AvailableProcessors();

String const _Enviroment::gWebSocketBufferSize =
    createString("env.ws.buffer.size");
int const _Enviroment::DefaultWebSocketBufferSize = 512 * 1024;

String const _Enviroment::gWebSocketRcvThreadsNum =
    createString("env.ws.threads.num");
long const _Enviroment::DefaultWebSocketRcvThreadsNum =
    st(System)::AvailableProcessors();

String const _Enviroment::gWebSocketFrameSize =
    createString("env.ws.frame.size");
int const _Enviroment::DefaultWebSocketFrameSize = 64 * 1024;

String const _Enviroment::gLocalSocketServerRcvBufferSize =
    createString("env.ls.server.rcv.size");
int const _Enviroment::DefaultLocalSocketServerRcvBufferSize = 64 * 1024;

String const _Enviroment::gLocalSocketServerClientNums =
    createString("env.ls.server.client.nums");
int const _Enviroment::DefaultLocalSocketServerClientNums = 64 * 1024;

String const _Enviroment::gTcpServerEpollSize =
    createString("env.tcp.server.epoll.size");
int const _Enviroment::DefaultTcpServerEpollSize = 8 * 1024;

String const _Enviroment::gTcpServerRcvBuffSize =
    createString("env.tcp.server.rcv.buffer.size");
int const _Enviroment::DefaultTcpServerRcvBuffSize = 64 * 1024;

String const _Enviroment::gTcpServerClientNums =
    createString("env.tcp.server.client.nums");
int const _Enviroment::DefaultTcpServerClientNums = 64 * 1024;

String const _Enviroment::gLocalSocketServerEpollSize =
    createString("env.ls.server.epoll.size");
int const _Enviroment::DefaultLocalSocketServerEpollSize = 8 * 1024;

String const _Enviroment::gLocalSocketBufferSize =
    createString("env.ls.buffer.size");
int const _Enviroment::DefaultLocalSocketBufferSize = 64 * 1024;

String const _Enviroment::gLocalSocketClientEpollSize =
    createString("env.ls.client.epoll.size");
int const _Enviroment::DefaultLocalSocketClientEpollSize = 8 * 1024;

String const _Enviroment::gAsyncTcpClientEpollSize =
    createString("env.aynsc.tcp.client.epoll.size");
int const _Enviroment::DefaultAsyncTcpClientEpollSize = 8 * 1024;

String const _Enviroment::gAsyncTcpClientBufferSize =
    createString("env.async.tcp.client.buffer.size");
int const _Enviroment::DefaultAsyncTcpClientBufferSize = 64 * 1024;

String const _Enviroment::gUdpClientEpollSize =
    createString("env.udp.client.epoll.size");
int const _Enviroment::DefaultUdpClientEpollSize = 8 * 1024;

String const _Enviroment::gUdpClientBufferSize =
    createString("env.udp.client.buffer.size");
int const _Enviroment::DefaultUdpClientBufferSize = 64 * 1024;

String const _Enviroment::gUdpServerEpollSize =
    createString("env.udp.server.epoll.size");
int const _Enviroment::DefaultUdpServerEpollSize = 8 * 1024;

String const _Enviroment::gUdpServerBufferSize =
    createString("env.udp.server.buffer.size");
int const _Enviroment::DefaultUdpServerBufferSize = 64 * 1024;

String const _Enviroment::gHttpServerPort = createString("http.server.port");
int const _Enviroment::DefaultHttpServerPort = 80;

String const _Enviroment::gHttpServerSendFileBufferSize =
    createString("http.server.sendfile.buffer.size");
int const _Enviroment::DefaultHttpServerSendFileBufferSize = 1024 * 128;

String const _Enviroment::gHttpMultiPartDispositionSize =
    createString("http.part.disposition.size");
int const _Enviroment::DefaultHttpMultiPartDispositionSize = 1024;

String const _Enviroment::gHttpMultiPartContentTypeSize =
    createString("http.part.contenttype.size");
;
int const _Enviroment::DefaultHttpMultiContentTypeSize = 1024;

String const _Enviroment::gHttpMultiPartContentSize =
    createString("http.part.content.size");
int const _Enviroment::DefaultHttpMultiContentSize = 32 * 1024;

String const _Enviroment::gHttpMultiPartFilePath =
    createString("http.part.file.path");
String const _Enviroment::DefaultMultiPartFilePath = createString("./tmp/");

String const _Enviroment::gHttpSslKeyPath = createString("https.ssl.key.path");
String const _Enviroment::DefaultHttpSslKeyPath = createString("");

String const _Enviroment::gHttpSslCertificatePath =
    createString("https.ssl.cert.path");
String const _Enviroment::DefaultHttpSslCertificatePath = createString("");

sp<_Enviroment> _Enviroment::getInstance() {
    static std::once_flag s_flag;
    std::call_once(s_flag, [&]() {
        _Enviroment *p = new _Enviroment();
        //p->mInstance.set_pointer(p);
        mInstance = AutoClone(p);
    });

    return mInstance;
}

_Enviroment::_Enviroment() {
    mProp = createHashMap<String, String>();

#define SET_VALUE(X,Y) mProp->put(X,createString(Y))

    SET_VALUE(gHttpBufferSize,DefaultHttpBufferSize);
    SET_VALUE(gHttpServerThreadsNum,DefaultgHttpServerThreadsNum);
    SET_VALUE(gWebSocketBufferSize,DefaultWebSocketBufferSize);
    SET_VALUE(gWebSocketBufferSize,DefaultWebSocketRcvThreadsNum);
    SET_VALUE(gWebSocketFrameSize,DefaultWebSocketFrameSize);
    SET_VALUE(gLocalSocketServerRcvBufferSize,DefaultLocalSocketServerRcvBufferSize);
    SET_VALUE(gLocalSocketServerClientNums,DefaultLocalSocketServerClientNums);
    SET_VALUE(gTcpServerEpollSize,DefaultTcpServerEpollSize);
    SET_VALUE(gTcpServerRcvBuffSize,DefaultTcpServerRcvBuffSize);
    SET_VALUE(gTcpServerClientNums,DefaultTcpServerClientNums);
    SET_VALUE(gLocalSocketServerEpollSize,DefaultLocalSocketServerEpollSize);
    SET_VALUE(gLocalSocketBufferSize,DefaultLocalSocketBufferSize);
    SET_VALUE(gLocalSocketClientEpollSize,DefaultLocalSocketClientEpollSize);
    SET_VALUE(gAsyncTcpClientEpollSize,DefaultAsyncTcpClientEpollSize);
    SET_VALUE(gAsyncTcpClientBufferSize,DefaultAsyncTcpClientBufferSize);
    SET_VALUE(gUdpClientEpollSize,DefaultUdpClientEpollSize);
    SET_VALUE(gUdpClientBufferSize,DefaultUdpClientBufferSize);
    SET_VALUE(gUdpServerEpollSize,DefaultUdpServerEpollSize);
    SET_VALUE(gUdpServerBufferSize,DefaultUdpServerBufferSize);
    SET_VALUE(gHttpServerPort, DefaultHttpServerPort);
    SET_VALUE(gHttpServerSendFileBufferSize,DefaultHttpServerSendFileBufferSize);
    SET_VALUE(gHttpMultiPartDispositionSize,DefaultHttpMultiPartDispositionSize);
    SET_VALUE(gHttpMultiPartContentTypeSize,DefaultHttpMultiContentTypeSize);
    SET_VALUE(gHttpMultiPartContentSize,DefaultHttpMultiContentSize);

#undef SET_VALUE

    mProp->put(gHttpMultiPartFilePath, DefaultMultiPartFilePath);
    mProp->put(gHttpSslKeyPath, DefaultHttpSslKeyPath);
    mProp->put(gHttpSslCertificatePath, DefaultHttpSslCertificatePath);
}

void _Enviroment::set(String tag, String v) {
    mProp->put(tag, v);
}

int _Enviroment::getInt(String v, int defaultvalue) {
    String value = mProp->get(v);
    return (value != nullptr)?value->toBasicInt():defaultvalue;
}

bool _Enviroment::getBoolean(String v, bool defaultvalue) {
    String value = mProp->get(v);
    return (value != nullptr)?value->toBasicBool():defaultvalue;
}

String _Enviroment::get(String v) {
    return mProp->get(v);
}

String _Enviroment::get(String v, String defaultvalue) {
    String value = mProp->get(v);
    return (value != nullptr)?value:defaultvalue;
}

} // namespace obotcha
