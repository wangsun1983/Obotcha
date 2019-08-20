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
#include "HttpParser.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

_HttpClient::_HttpClient() {
    mPort = 80;
    mTimeout = 5000;
}

void _HttpClient::setUrl(String url) {

}


void _HttpClient::setTimeout(int timeout) {

}

void _HttpClient::setKeepAlive(bool keepalive) {

}

String _HttpClient::getIp() {

}

String _HttpClient::getUrl() {

}

int _HttpClient::getPort() {

}

int _HttpClient::getTimeout() {

}

bool _HttpClient::getKeepAlive() {
   
}

int _HttpClient::connect() {

}

int _HttpClient::bindServerByDomain(String host,int port) {
    if(host == nullptr) {
        return -HttpClientParamErr;
    }

    mHost = host;
    //we need get ip for url
    ArrayList<String> ips = st(InetAddress)::getHostByName(host);
    if(ips == nullptr || ips->size() == 0) {
        mHost = nullptr;
        return -HttpClientConnectFail;
    }

    mIp = ips->get(0);
    mPort = port;
    return 0;
}

int _HttpClient::bindServerByIp(String ip,int port) {
    if(ip == nullptr) {
        return -HttpClientParamErr;
    }
    mIp = ip;
    mPort = port;
    return 0;
}

int _HttpClient::unbindServer(String host) {
    mHost = nullptr;
}

String _HttpClient::execute(int method,HttpUrl url) {
    HttpPacket packet = createHttpPacket();
    packet->setMethod(method);
    packet->setUrl(url->getPath());
    packet->getHeader()->setValue(Http_Header_Host,url->getHost());
    //packet->getHeader()->setValue(Http_Header_User_Agent,"User-Agent: Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0");
    //packet->getHeader()->setValue(Http_Header_Accept," text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8");
    //packet->getHeader()->setValue(Http_Header_Accept_Language,"en-US,en;q=0.5");
    //packet->getHeader()->setValue(Http_Header_Referer,"http://www.tusvisionai.com/about");
    //packet->getHeader()->setValue(Http_Header_Connection,"keep-alive");
    //this is not bind client
    String ip = mIp;
    if(mIp == nullptr) {
        ArrayList<String> ips = st(InetAddress)::getHostByName(url->getHost());
        if(ips == nullptr || ips->size() == 0) {
            return nullptr;
        }

        ip = ips->get(0);
        mTcpClient = createTcpClient(ip,mPort,mTimeout);
    }

    if(!mKeepAlive) {
        mTcpClient->doConnect();
    }
    //printf("packet->genHttp is %s \n",packet->genHttpRequest()->toChars());
    mTcpClient->doSend(createByteArray(packet->genHttpRequest()));
    
    ByteArray result = mTcpClient->doReceive();
    //while(1) {
    //    result = mTcpClient->doReceive();
    //    printf("%s \n",result->toString()->toChars());
    //}

    //get first block
    HttpParser parser = createHttpParser();
    HttpPacket firstBlock = parser->parseResponse(result->toString());
    String transferEncoding = firstBlock->getHeader()->getValue(Http_Header_Transfer_Encoding);
    if(transferEncoding!= nullptr && transferEncoding->equals("chunked")) {
        result = doReceiveChunk(result);
    } else {
        //TODO
    }
    printf("accept result is %s \n",result->toString()->toChars());

    if(!mKeepAlive) {
        mTcpClient->release();
    }
    
    return result->toString();
}

String _HttpClient::execute(int,String url) {
    //TODO
}

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
            //printf("http data is %s \n",httpdata->toString()->toChars());
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

}

