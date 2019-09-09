#ifndef __HTTP_CLIENT_HPP__
#define __HTTP_CLIENT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpClient) {

public:
    _HttpClient();
    
    int bindServerByDomain(String host,int port=80);

    int bindServerByIp(String ip,int port);

    int unbindServer(String host);

    //void setIp(String ip);

    void setUrl(String url);

    //void setPort(int port);

    void setTimeout(int timeout);

    void setKeepAlive(bool keepalive);
    
    String getIp();

    String getUrl();

    int getPort();

    int getTimeout();

    bool getKeepAlive();

    int connect();

    String execute(int,HttpUrl);

    String execute(int,String url);

private:
    String mIp;

    String mUrl;

    String mHost;
    
    int mPort;
    
    int mTimeout;
    
    bool mKeepAlive; 

    TcpClient mTcpClient;

    ByteArray doReceiveChunk(ByteArray firstBlock);

    ByteArray doReceiveEntity(ByteArray firstBlock);
};

}
#endif
