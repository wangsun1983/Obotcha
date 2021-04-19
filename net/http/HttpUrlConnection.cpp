#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "SocketBuilder.hpp"
#include "HttpUrl.hpp"
#include "HttpUrlConnection.hpp"
#include "HttpRequestWriter.hpp"
#include "SocketListener.hpp"
#include "URL.hpp"

namespace obotcha {

_HttpUrlConnection::_HttpUrlConnection(HttpUrl url):_HttpUrlConnection(url,nullptr) {
    
}

_HttpUrlConnection::_HttpUrlConnection(sp<_HttpUrl> url,Handler h) {
    mUrl = url;
    mParser = createHttpPacketParser();
    mHandler = h;
    mListener = nullptr;
}

void _HttpUrlConnection::setListener(HttpConnectionListener l) {
    mListener = l;
}

_HttpUrlConnection* _HttpUrlConnection::setTimeout(int timeout) {
    mTimeout = timeout;
    return this;
}

_HttpUrlConnection* _HttpUrlConnection::setKeepAlive(bool keepalive) {
    mKeepAlive = keepalive;
    return this;
}

bool _HttpUrlConnection::isKeepAlive() {
    return mKeepAlive;
}

int _HttpUrlConnection::connect() {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpUrlConnection *url) {
            int ret = url->_connect();
            url->mListener->onConnect(ret);
        },this);
    } else {
        return _connect();
    }

    return 0;
}

HttpResponse _HttpUrlConnection::execute(HttpRequest req) {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpUrlConnection *url,HttpRequest req) {
            url->_execute(req);
        },this,req);
    } else {
        return _execute(req);
    }

    return nullptr;
}

int _HttpUrlConnection::_connect() {
    printf("mUrl host is %s \n",mUrl->getHost()->toChars());
    ArrayList<InetAddress> address = createURL(mUrl->getHost())->getInetAddress();
    if(address == nullptr || address->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress inetAddr = address->get(0);
    printf("addr is %s \n",inetAddr->getAddress()->toChars());
    inetAddr->setPort(mUrl->getPort());
    mSocket = createSocketBuilder()->setAddress(inetAddr)->newSocket();
    int result = mSocket->connect();
    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket);

    return result;
}

HttpResponse _HttpUrlConnection::_execute(HttpRequest req) {
    //check whether httpurl is still connect
    writer->write(req);
    while(1) {
        ByteArray result = createByteArray(1024*64);
        int len = mInputStream->read(result);
        result->quickShrink(len);
        mParser->pushHttpData(result);
        ArrayList<HttpPacket> packets = mParser->doParse();
        if(packets->size() > 0) {
            return createHttpResponse(packets->get(0));
        }
    }

    return nullptr;
}

int _HttpUrlConnection::close() {
    mSocket->close();
    return 0;
}

void _HttpUrlConnection::onResponse(int event,ByteArray r) {
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
                    mListener->onResponse(Cast<HttpResponse>(iterator->getValue()));
                    iterator->next();
                }
            }
            break;
    }
}

}

