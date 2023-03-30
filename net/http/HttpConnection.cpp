#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "Error.hpp"
#include "HttpConnection.hpp"
#include "HttpHeader.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "HttpUrl.hpp"
#include "Inet4Address.hpp"
#include "InetAddress.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "HttpPacketParserImpl.hpp"
#include "InfiniteLoop.hpp"

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
            return -ENOTCONN;
        }
        inetAddr->setAddress(address->get(0)->getAddress());
    }
    
    auto builder = createSocketBuilder();
    builder->setAddress(inetAddr)->setOption(mOption);

    switch(mUrl->getScheme()) {
        case st(NetProtocol)::Http:
        case st(NetProtocol)::Ws:
            mSocket = builder->newSocket();
        break;

        default:
            mSocket = builder->newSSLSocket();        
    }

    if (mSocket->connect() < 0) {
        LOG(ERROR) << "Connect failed,reason is " << strerror(errno);
        return -ENOTCONN;
    }

    mInputStream = mSocket->getInputStream();
    mWriter = createHttpPacketWriterImpl(mSocket->getOutputStream());
    return 0;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    AutoLock l(mMutex);
    if (mWriter->write(req) < 0) {
        LOG(ERROR) << "Cannot send request!!!";
        return nullptr;
    }

    int buffsize = 0;
    if((mOption == nullptr || (buffsize = mOption->getRcvBuffSize()) == -1)) {
        buffsize = st(HttpOption)::DefaultBuffSize;
    }

    ByteArray result = createByteArray(buffsize);
    InfiniteLoop {
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
