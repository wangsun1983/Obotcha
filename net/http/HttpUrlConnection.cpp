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

_HttpUrlConnection::_HttpUrlConnection(HttpUrl url,HttpOption option):_HttpUrlConnection(url,nullptr,option) {
    
}

_HttpUrlConnection::_HttpUrlConnection(sp<_HttpUrl> url,Handler h,HttpOption option) {
    mUrl = url;
    mParser = createHttpPacketParser();
    mHandler = h;
    mListener = nullptr;
    mOption = option;
}

void _HttpUrlConnection::setListener(HttpConnectionListener l) {
    mListener = l;
}

Socket _HttpUrlConnection::getSocket() {
    return mSocket;
}

int _HttpUrlConnection::connect() {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpUrlConnection *url) {
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

HttpResponse _HttpUrlConnection::execute(HttpRequest req) {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpUrlConnection *url,HttpRequest req) {
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

void _HttpUrlConnection::execute(HttpRequest req,int what) {
    if(mHandler != nullptr) {
        mHandler->post([](_HttpUrlConnection *url,HttpRequest req,int what) {
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

int _HttpUrlConnection::_connect() {
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

HttpResponse _HttpUrlConnection::_execute(HttpRequest req) {
    //check whether httpurl is still connect
    printf("_HttpUrlConnection execute \n");
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


}

