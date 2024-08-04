#include "ArrayList.hpp"
#include "Error.hpp"
#include "HttpConnection.hpp"
#include "HttpPacketWriterImpl.hpp"
#include "HttpUrl.hpp"
#include "Inet4Address.hpp"
#include "InetAddress.hpp"
#include "Log.hpp"
#include "SocketBuilder.hpp"
#include "ExecutorBuilder.hpp"

namespace obotcha {

_HttpConnection::_HttpConnection(sp<_HttpUrl> url, HttpOption option):mUrl(url),mOption(option) {
    mParser = HttpPacketParserImpl::New();
    mExecutor = ExecutorBuilder::New()
                ->setDefaultThreadNum(1)
                ->newThreadPool();
}

Socket _HttpConnection::getSocket() { 
    return mSocket; 
}

int _HttpConnection::connect() {
    InetAddress inetAddr = nullptr;
    
    if (mUrl->getHost() != nullptr) {
        ArrayList<InetAddress> address = mUrl->getInetAddress();
        if (address == nullptr || address->size() == 0) {
            return -ENOTCONN;
        }
        inetAddr = address->get(0);
    }
    
    auto builder = SocketBuilder::New();
    builder->setAddress(inetAddr)->setOption(mOption);

    switch(mUrl->getScheme()) {
        case st(Net)::Protocol::Http:
        case st(Net)::Protocol::Ws:
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
    mWriter = HttpPacketWriterImpl::New(mSocket->getOutputStream());
    return 0;
}

HttpResponse _HttpConnection::execute(HttpRequest req) {
    if (mWriter->write(req) < 0) {
        LOG(ERROR) << "Cannot send request!!!";
        return nullptr;
    }

    int buffsize = (mOption == nullptr)?(st(HttpOption)::DefaultBuffSize):
                                        mOption->getRcvBuffSize();
    
    ByteArray result = ByteArray::New(buffsize);
    while(true) {
        auto len = mInputStream->read(result);
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
            return HttpResponse::New(packets->get(0));
        }
    }
}

void _HttpConnection::execute(HttpRequest r,Message m) {
    mExecutor->submit([this](HttpRequest req,Message msg){
        auto resp = execute(req);
        if(msg != nullptr) {
            msg->data = resp;
            msg->sendToTarget();
        }
    },r,m);
}

void _HttpConnection::send(HttpRequest r) {
    execute(r,nullptr);
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

    if(mExecutor != nullptr) {
        mExecutor->shutdown();
        mExecutor->awaitTermination();
        mExecutor = nullptr;
    }
    return 0;
}

_HttpConnection::~_HttpConnection() {
    close();
}

} // namespace obotcha
