#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "HashMap.hpp"
#include "HttpConnection.hpp"
#include "HttpConnectionListener.hpp"
#include "HttpHeader.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "HttpUrl.hpp"
#include "Inet4Address.hpp"
#include "InetAddress.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "SocketListener.hpp"
#include "String.hpp"
#include "System.hpp"
#include "HttpPacketParserImpl.hpp"
#include "NetEvent.hpp"

namespace obotcha {

_HttpConnection::_HttpConnection(sp<_HttpUrl> url, HttpOption option) {
    mUrl = url;
    mParser = createHttpPacketParserImpl();
    mOption = option;
    mMutex = createMutex();
}

Socket _HttpConnection::getSocket() { 
    return mSocket; 
}

int _HttpConnection::connect() {
    InetAddress inetAddr = createInet4Address(mUrl->getPort());

    if (mUrl->getHost() != nullptr) {
        ArrayList<InetAddress> address = mUrl->getInetAddress();
        if (address == nullptr || address->size() == 0) {
            return -NetConnectFail;
        }

        inetAddr->setAddress(address->get(0)->getAddress());
    }
    
    if(mUrl->getScheme() == st(NetProtocol)::Http) {
        mSocket = createSocketBuilder()
                    ->setAddress(inetAddr)
                    ->setOption(mOption)
                    ->newSocket();
    } else {
        mSocket = createSocketBuilder()
                    ->setAddress(inetAddr)
                    ->setOption(mOption)
                    ->newSSLSocket();
    }

    if (mSocket->connect() < 0) {
        LOG(ERROR) << "Connect failed,reason is " << strerror(errno);
        return -NetConnectFail;
    }

    mInputStream = mSocket->getInputStream();
    writer = createHttpPacketWriterImpl(mSocket->getOutputStream());

    return 0;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    AutoLock l(mMutex);
    if (writer->write(req) < 0) {
        LOG(ERROR) << "Cannot send request!!!";
        return nullptr;
    }

    int buffsize = (mOption == nullptr ? st(HttpOption)::DefaultBuffSize
                                       : mOption->getBuffSize());

    ByteArray result = createByteArray(buffsize);
    while (1) {
        int len = mInputStream->read(result);
        if (len <= 0) {
            mParser->reset();
            LOG(ERROR) << "Cannot get response!!!,len is " << len;
            return nullptr;
        }

        result->quickShrink(len);
        mParser->pushData(result);

        ArrayList<HttpPacket> packets = mParser->doParse();
        result->quickRestore();
        if (packets == nullptr) {
            continue;
        } else if (packets->size() > 1) {
            mParser->reset();
            LOG(ERROR) << "get too many responses,size is " << packets->size();
        } else if (packets->size() == 1) {
            return createHttpResponse(packets->get(0));
        }
    }

    return nullptr;
}

int _HttpConnection::close() {
    if(mSocket != nullptr) {
        mSocket->close();
        mSocket = nullptr;
    }

    if(mInputStream != nullptr) {
        mInputStream->close();
        mInputStream = nullptr;
    }
    return 0;
}

} // namespace obotcha
