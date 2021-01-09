#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpClient.hpp"
#include "HttpPacket.hpp"
#include "InetAddress.hpp"
#include "HttpHeader.hpp"
#include "ByteArrayReader.hpp"
#include "Error.hpp"
#include "HttpV1ResponseParser.hpp"

namespace obotcha {

_HttpClient::_HttpClient() {
    mPort = 80;
    mTimeout = 5000;
    mParser = createHttpV1ResponseParser();
}

void _HttpClient::setUrl(String url) {

}


void _HttpClient::setTimeout(int timeout) {

}

void _HttpClient::setKeepAlive(bool keepalive) {

}

String _HttpClient::getIp() {
    //TODO
    return nullptr;
}

String _HttpClient::getUrl() {
    //TODO
    return nullptr;
}

int _HttpClient::getPort() {
    //TODO
    return 0;
}

int _HttpClient::getTimeout() {
    //TODO
    return 0;
}

bool _HttpClient::getKeepAlive() {
   //TODO
   return false;
}

int _HttpClient::connect() {
   //TODO
   return 0;
}

int _HttpClient::bindServerByDomain(String host,int port) {
    if(host == nullptr) {
        return -InvalidParam;
    }

    mHost = host;
    //we need get ip for url
    ArrayList<String> ips = st(InetAddress)::getHostByName(host);
    if(ips == nullptr || ips->size() == 0) {
        mHost = nullptr;
        return -NetConnectFail;
    }

    mIp = ips->get(0);
    mPort = port;
    return 0;
}

int _HttpClient::bindServerByIp(String ip,int port) {
    if(ip == nullptr) {
        return -InvalidParam;
    }
    mIp = ip;
    mPort = port;
    return 0;
}

int _HttpClient::unbindServer(String host) {
    mHost = nullptr;
    //TODO
    return 0;
}

String _HttpClient::execute(int method,HttpUrl url) {
    HttpPacket packet = createHttpPacket();
    packet->setMethod(method);
    packet->setUrl(url->getPath());
    packet->getHeader()->setValue(st(HttpHeader)::Host,url->getHost());
    //packet->getHeader()->setValue(Http_Header_User_Agent,"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
    //packet->getHeader()->setValue(Http_Header_Accept," text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //packet->getHeader()->setValue(Http_Header_Accept_Language,"en-US,en;q=0.5");
    //packet->getHeader()->setValue(Http_Header_Referer,"http://www.tusvisionai.com/about");
    //packet->getHeader()->setValue(Http_Header_Connection,"keep-alive");
    //this is not bind client

    ArrayList<String> ips = st(InetAddress)::getHostByName(url->getHost());
    if(ips == nullptr || ips->size() == 0) {
        return nullptr;
    }

    String ip = ips->get(0);
    printf("ip is %s \n",ip->toChars());
    mTcpClient = createTcpClient(ip,url->getPort());
   

    //if(!mKeepAlive) {
    mTcpClient->doConnect();
    //}
    int len = mTcpClient->doSend(createByteArray(packet->genHttpRequest()));
    printf("len is %d \n",len);
    while(1) {
        ByteArray result = mTcpClient->doReceive();
        printf("receive \n");
        mParser->pushHttpData(result);
        ArrayList<HttpPacket> packets = mParser->doParse();
        if(packets == nullptr || packets->size() == 0) {
            continue;
        }
        return packets->get(0)->getBody()->toString();
    }
    
    return nullptr;
}

String _HttpClient::execute(int,String url) {
    //TODO
    return nullptr;
}

/*
ByteArray _HttpClient::doReceiveChunk(ByteArray firstBlock) {
    //find first data length
    ByteArrayReader reader = createByteArrayReader(firstBlock);
    ByteArray mBody = nullptr;
    //check first block
    int chunksize = 0;
    while(1) {
        String nextLine = reader->readLine();

        if(nextLine == nullptr) {
            break;
        }

        if(nextLine->size() != 0) {
            continue;
        }
        nextLine = reader->readLine();
        
        chunksize = nextLine->toHexInt();
        break;
    }

    while(1) {
        if(chunksize == 0){
            break;
        }

        ByteArray data = createByteArray(chunksize);
        while(reader->getRemainSize() < chunksize) {
            ByteArray httpdata = mTcpClient->doReceive();
            reader->appendWithAdjustment(httpdata);
        }
        reader->readByteArray(data);
        if(mBody == nullptr) {
            mBody = data;
        } else {
            mBody->append(data);
        }
        
        while(1) {
            int lastIndex = reader->getIndex();
            String nextChunkStr = reader->readLine();
            if(nextChunkStr->size() == 0) {
                continue;
            }

            if(nextChunkStr == nullptr) {
                ByteArray httpdata = mTcpClient->doReceive();
                reader->setIndex(lastIndex);
                reader->appendWithAdjustment(httpdata);
            } else {
                chunksize = nextChunkStr->toHexInt();
                break;
            }
        }
    }
    
    return mBody;
}
 */
}

