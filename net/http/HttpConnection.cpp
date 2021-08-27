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
#include "Log.hpp"

namespace obotcha {

SocketMonitor _HttpConnection::mSocketMonitor = nullptr;

_HttpConnection::_HttpConnection(sp<_HttpUrl> url,bool async, HttpConnectionListener l, HttpOption option) {
    isAsync = async;
    mUrl = url;
    mParser = createHttpPacketParser();
    mOption = option;
    mListener = l;
}

Socket _HttpConnection::getSocket() {
    return mSocket;
}

int _HttpConnection::connect() {
    ArrayList<InetAddress> address = createURL(mUrl->getHost())->getInetAddress();
    if(address == nullptr || address->size() == 0) {
        return -NetConnectFail;
    }

    InetAddress inetAddr = address->get(0);
    inetAddr->setPort(mUrl->getPort());

    mSocket = createSocketBuilder()->setAddress(inetAddr)->setOption(mOption)->newSocket();
    int result = mSocket->connect();
    if(result < 0) {
        return result;
    }

    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket->getOutputStream());

    if(isAsync) {
        static std::once_flag flag;
        std::call_once(flag, [&]() {
            mSocketMonitor = createSocketMonitor();
        });

        mSocketMonitor->bind(mSocket,AutoClone(this));
    }
    return result;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    if(writer->write(req) <= 0) {
        return nullptr;
    }

    if(isAsync) {
        return createHttpResponse(); //return dummy response
    }

    int buffsize = (mOption == nullptr?st(HttpOption)::DefaultBuffSize:mOption->getBuffSize());
    ByteArray result = createByteArray(buffsize);

    while(1) {
        int len = mInputStream->read(result);
        if(len <= 0) {
            mParser->reset();
            LOG(ERROR)<<"Cannot get response!!!,len is "<<len;
            return nullptr;
        }

        result->quickShrink(len);
        mParser->pushHttpData(result);
        ArrayList<HttpPacket> packets = mParser->doParse();
        result->quickRestore();
        if(packets == nullptr) {
            continue;
        } else if(packets->size() > 1) {
            mParser->reset();
            LOG(ERROR)<<"get too many responses,size is "<<packets->size();
        } else if(packets->size() == 1) {
            return createHttpResponse(packets->get(0));
        } 
    }
    return nullptr;
}

int _HttpConnection::close() {
    if(isAsync) {
        mSocketMonitor->remove(mSocket);
    }

    mSocket->close();
    return 0;
}

void _HttpConnection::onSocketMessage(int event,Socket sock,ByteArray data) {
    switch(event) {
        case st(SocketListener)::Disconnect:
            mListener->onDisconnect();
            break;

        case st(SocketListener)::Message:
            mParser->pushHttpData(data);
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

