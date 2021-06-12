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

_HttpConnection::_HttpConnection(HttpUrl url,HttpOption option) {
    mUrl = url;
    mParser = createHttpPacketParser();
    mOption = option;
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
    mInputStream = mSocket->getInputStream();
    writer = createHttpRequestWriter(mSocket->getOutputStream());
    return result;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    if(writer->write(req) <= 0) {
        return nullptr;
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
    mSocket->close();
    return 0;
}


}

