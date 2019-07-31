#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <netinet/in.h>
#include <mqueue.h>
#include <fstream>
#include <sys/un.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "SocketListener.hpp"
#include "Mutex.hpp"
#include "Pipe.hpp"
#include "AtomicInteger.hpp"
#include "Thread.hpp"
#include "TcpServer.hpp"
#include "WebSocketListener.hpp"
#include "SocketListener.hpp"
#include "EPollFileObserver.hpp"
#include "Mutex.hpp"
#include "HttpParser.hpp"
#include "WebSocketFrameComposer.hpp"
#include "WebSocketParser.hpp"
#include "HashMap.hpp"
#include "WebSocketClient.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlParser.hpp"
#include "WebSocketProtocol.hpp"

namespace obotcha {


_WebSocketTcpClientListener::_WebSocketTcpClientListener(WebSocketListener l) {
    mWsListener = l;
}
    
void _WebSocketTcpClientListener::onAccept(int fd,String ip,int port,ByteArray pack) {
    printf("accept pack is %s \n",pack->toValue());
}

void _WebSocketTcpClientListener::onDisconnect(int fd) {

}

void _WebSocketTcpClientListener::onConnect(int fd,String ip,int port) {

}

void _WebSocketTcpClientListener::onConnect(int fd,String domain) {

}

_WebSocketClient::_WebSocketClient() {
    mComposer = createWebSocketFrameComposer(true);
}

int _WebSocketClient::bind(String url,WebSocketListener l) {
    //send http request
    //mObserver = createEPollFileObserver();
    HttpRequest request = createHttpRequest();
    request->setMethod(HttpMethodGet);
    
    HttpUrl httpUrl = st(HttpUrlParser)::parseUrl(url);
    //printf("httpUrl path is %s,url is %s \n",httpUrl->getHost()->toChars(),httpUrl->getPath()->toChars());
    //printf("port is %d \n",httpUrl->getPort());
    request->setUrl(httpUrl->getPath());
    request->setMajorVersion(1);
    request->setMinorVersion(1);

    String host = httpUrl->getHost()->append(":")->append(createString(httpUrl->getPort()));
    request->getHeader()->setValue(Http_Header_Host,host);

    request->getHeader()->setValue(Http_Header_Accept,"*/*");
    request->getHeader()->setValue(Http_Header_Accept_Language,"en-US,en;q=0.5");
    request->getHeader()->setValue(Http_Header_Accept_Encoding,"gzip, deflate");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Version,"13");
    request->getHeader()->setValue(Http_Header_Origin,"null");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Extensions,"permessage-deflate");
    request->getHeader()->setValue(Http_Header_Sec_WebSocket_Key,"fYbVEMSirecOe/q+edVT+w==");
    request->getHeader()->setValue(Http_Header_Connection,"keep-alive, Upgrade");
    request->getHeader()->setValue(Http_Header_Upgrade,"websocket");
    request->getHeader()->setValue(Http_Header_Pragma,"no-cache");
    request->getHeader()->setValue(Http_Header_Cache_Control,"no-cache");

    String shakeHandMsg = request->genHttpString();
    //printf("request is %s \n",shakeHandMsg->toChars());

    mListener = createWebSocketTcpClientListener(l);

    mTcpClient = createTcpClient(httpUrl->getHost(),httpUrl->getPort(),mListener);
    mTcpClient->start();

    mTcpClient->send(createByteArray(shakeHandMsg));

    return 0;
}

int _WebSocketClient::sendMessage(String msg) {
    mTcpClient->send(mComposer->generateMessageFrame(
        st(WebSocketProtocol)::OPCODE_TEXT,
        createByteArray(msg)));
}


}


