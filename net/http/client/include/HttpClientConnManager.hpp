#ifndef __OBOTCHA_HTTP_CLIENT_CONN_MANAGER_HPP__
#define __OBOTCHA_HTTP_CLIENT_CONN_MANAGER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HttpConnection.hpp"
#include "ConcurrentHashMap.hpp"
#include "String.hpp"
#include "Integer.hpp"

namespace obotcha {

DECLARE_CLASS(HttpClientConnKey) {
public:
    String host;
    String path;
    int scheme;
    int port;

    _HttpClientConnKey(int scheme,String host,String path,int port = 80);
    bool equals(HttpClientConnKey);
    uint64_t hashcode();
};

DECLARE_CLASS(HttpClientConnManager) {
public:
    _HttpClientConnManager();
    HttpConnection get(HttpClientConnKey);
    void add(HttpClientConnKey,HttpConnection);
    void remove(HttpClientConnKey);

private:
    ConcurrentHashMap<HttpClientConnKey,HttpConnection> pool;
};

}

#endif