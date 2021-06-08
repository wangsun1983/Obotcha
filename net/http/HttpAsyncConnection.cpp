#include "Object.hpp"
#include "StrongPointer.hpp"

#include "HttpAsyncConnection.hpp"
#include "HttpAsyncConnectionPool.hpp"
#include "SocketListener.hpp"
#include "URL.hpp"
#include "SocketBuilder.hpp"

namespace obotcha {


_HttpAsyncConnection::_HttpAsyncConnection(sp<_HttpUrl> url,HttpConnectionListener l,HttpOption option) {
    mUrl = url;
    mListener = l;
    mOption = option;
    mParser = createHttpPacketParser();
    mSocket = nullptr;
    writer = nullptr;
    mInputStream = nullptr;
    //TODO?
    mPool = nullptr;
}

int _HttpAsyncConnection::connect() {
    ArrayList<InetAddress> address = createURL(mUrl->getHost())->getInetAddress();
    if(address == nullptr || address->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress inetAddr = address->get(0);
    inetAddr->setPort(mUrl->getPort());

    mSocket = createSocketBuilder()
                ->setOption(mOption)
                ->setAddress(inetAddr)
                ->newSocket();

    int result = mSocket->connect();
    mSocket->setAsync(true);
    
    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket->getOutputStream());

    return result;
}

int _HttpAsyncConnection::execute(HttpRequest req) {
    return writer->write(req);
}

int _HttpAsyncConnection::close() {
    if(mPool != nullptr) {
        mPool->recyleConnection(AutoClone(this));
        mPool = nullptr;
    }

    if(mSocket != nullptr) {
        mSocket->close();
    }

    return 0;
}

void _HttpAsyncConnection::onResponse(int event,ByteArray r) {
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
