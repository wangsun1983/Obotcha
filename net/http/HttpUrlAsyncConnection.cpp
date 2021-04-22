#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpUrlAsyncConnection.hpp"
#include "SocketListener.hpp"
#include "URL.hpp"
#include "SocketBuilder.hpp"

namespace obotcha {


_HttpUrlAsyncConnection::_HttpUrlAsyncConnection(sp<_HttpUrl> url,HttpAsyncConnectionListener l,HttpOption option) {
    mUrl = url;
    mListener = l;
    mOption = option;
    mParser = createHttpPacketParser();
}

int _HttpUrlAsyncConnection::connect() {
    ArrayList<InetAddress> address = createURL(mUrl->getHost())->getInetAddress();
    if(address == nullptr || address->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress inetAddr = address->get(0);
    inetAddr->setPort(mUrl->getPort());
    mSocket = createSocketBuilder()->setAddress(inetAddr)->newSocket();
    int result = mSocket->connect();
    mSocket->setAsync();
    
    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket->getOutputStream());

    return result;
}

int _HttpUrlAsyncConnection::execute(HttpRequest req) {
    return writer->write(req);
}

int _HttpUrlAsyncConnection::close() {
    //TODO
}

void _HttpUrlAsyncConnection::onResponse(int event,ByteArray r) {
    if(mListener == nullptr) {
        return;
    }

    switch(event) {
        case st(SocketListener)::Disconnect:
            mListener->onDisconnect();
            break;

        case st(SocketListener)::Message:
            mParser->pushHttpData(r);
            ArrayList<HttpPacket> responses = mParser->doParse();
            if(responses->size() > 0) {
                ListIterator<HttpPacket> iterator = responses->getIterator();
                while(iterator->hasValue()) {
                    mListener->onResponse(createHttpResponse(iterator->getValue()));
                    iterator->next();
                }
            }
            break;
    }
}

}
