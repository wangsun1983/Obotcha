#include "HttpClient.hpp"

namespace obotcha {

HttpClientConnManager _HttpClient::connMgr = nullptr;

_HttpClient::_HttpClient() {
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        connMgr = createHttpClientConnManager();
    });
}

_HttpClient::~_HttpClient() {
    if(mCurrentUrl != nullptr) {
        auto c = connMgr->get(mCurrentUrl);
        if(c != nullptr) {
            c->close();
            connMgr->remove(mCurrentUrl);
        }
        mCurrentUrl = nullptr;
    }
}

HttpResponse _HttpClient::execute(HttpClientBaseRequest r,HttpOption option) {
    mCurrentUrl = r->getUrl();
    r->getHeader()->setHost(mCurrentUrl->getHost());

    auto c = connMgr->get(createHttpClientConnKey(mCurrentUrl->getHost(),mCurrentUrl->getPort()));
    HttpResponse response = nullptr;

    while(1) {
        if(c == nullptr) {
            c = createHttpConnection(mCurrentUrl,option);
            c->connect();
        }
        
        response = c->execute(r);
        if(response == nullptr && errno == EPIPE) {
            continue;
        }
        return response;
    }

    return nullptr;
}



}

