#include "HttpClientConnManager.hpp"

namespace obotcha {

_HttpClientConnKey::_HttpClientConnKey(st(Net)::Protocol param_scheme,
                                    String param_host,
                                    String param_path,
                                    int param_port):
                                    host(param_host),scheme(static_cast<int>(param_scheme)),
                                    port(param_port) {
    path = (param_path == nullptr)?createString(""):param_path;
}

bool _HttpClientConnKey::equals(Object key) {
    auto k = Cast<HttpClientConnKey>(key);
    return scheme == k->scheme && host->equals(k->host) && port == k->port && path->equals(k->path);
}

uint64_t _HttpClientConnKey::hashcode() const {
    return createString(scheme)->append(host,createString(port),path)->hashcode();
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
