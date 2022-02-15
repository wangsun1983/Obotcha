#include "HttpClientConnManager.hpp"

namespace obotcha {

_HttpClientConnKey::_HttpClientConnKey(String host,String path,int port) {
    this->host = host;
    this->port = port;
    this->path = path;
    if(path == nullptr) {
        path = createString("");
    }
}

bool _HttpClientConnKey::equals(HttpClientConnKey k) {
    return host->equals(k->host) && port == k->port && path->equals(k->path);
}

uint64_t _HttpClientConnKey::hashcode() {
    return host->append(createString(port),path)->hashcode();
}

_HttpClientConnManager::_HttpClientConnManager() {
    pool = createConcurrentHashMap<HttpClientConnKey,HttpConnection>();
}

HttpConnection _HttpClientConnManager::get(HttpClientConnKey k) {
    return pool->get(k);
}

void _HttpClientConnManager::add(HttpClientConnKey k,HttpConnection c) {
    pool->put(k,c);
}

void _HttpClientConnManager::remove(HttpClientConnKey k) {
    pool->remove(k);
}


}
