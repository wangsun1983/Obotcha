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
#include "HttpConnection.hpp"
#include "HttpConnectionListener.hpp"
#include "HttpRequestWriter.hpp"
#include "SocketListener.hpp"
#include "URL.hpp"

namespace obotcha {

_HttpConnection::_HttpConnection(HttpUrl url,HttpOption option):_HttpConnection(url,nullptr,option) {
    
}

_HttpConnection::_HttpConnection(sp<_HttpUrl> url,Handler h,HttpOption option) {
    mUrl = url;
    mParser = createHttpPacketParser();
    mHandler = h;
    mListener = nullptr;
    mOption = option;
}

void _HttpConnection::setListener(HttpConnectionListener l) {
    mListener = l;
}

Socket _HttpConnection::getSocket() {
    return mSocket;
}

int _HttpConnection::connect() {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpConnection *url) {
            int ret = url->_connect();
            if(url->mListener != nullptr) {
                url->mListener->onConnect(ret);
            }
        },this);
    } else {
        return _connect();
    }

    return 0;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpConnection *url,HttpRequest req) {
            HttpResponse response = url->_execute(req);
            Message msg = url->mHandler->obtainMessage();
            msg->data = Cast<Object>(response);
            url->mHandler->sendMessage(msg);
        },this,req);
    } else {
        return _execute(req);
    }

    return nullptr;
}

void _HttpConnection::execute(HttpRequest req,int what) {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpConnection *url,HttpRequest req,int what) {
            HttpResponse response = url->_execute(req);
            Message msg = url->mHandler->obtainMessage();
            msg->what = what;
            msg->data = Cast<Object>(response);
            url->mHandler->sendMessage(msg);
        },this,req,what);
    } else {
        _execute(req);
    }
}

int _HttpConnection::_connect() {
    ArrayList<InetAddress> address = createURL(mUrl->getHost())->getInetAddress();
    if(address == nullptr || address->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress inetAddr = address->get(0);
    inetAddr->setPort(mUrl->getPort());

    //TODO: add some option
    mSocket = createSocketBuilder()->setAddress(inetAddr)->newSocket();
    int result = mSocket->connect();
    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket->getOutputStream());

    return result;
}

HttpResponse _HttpConnection::_execute(HttpRequest req) {
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

int _HttpConnection::close() {
    mSocket->close();
    return 0;
}


}

