#include "HttpClient.hpp"

namespace obotcha {

HttpClientConnManager _HttpClient::connMgr = nullptr;

_HttpClient::_HttpClient() {
    static std::once_flag flag;
    std::call_once(flag, [&]() {
        connMgr = createHttpClientConnManager();
    });
    
    mCurrentUrl = nullptr;
}

_HttpClient::~_HttpClient() {
    close();
}

HttpResponse _HttpClient::execute(HttpClientBaseRequest r,HttpOption option) {
    auto formerUrl = mCurrentUrl;
    mCurrentUrl = r->getUrl();
    r->getHeader()->setHost(createHttpHeaderHost(mCurrentUrl->getHost(),mCurrentUrl->getPort()));
    r->getHeader()->setUrl(mCurrentUrl);
    HttpClientConnKey key = createHttpClientConnKey(mCurrentUrl->getScheme(),
                                                    mCurrentUrl->getHost(),
                                                    mCurrentUrl->getPath(),
                                                    mCurrentUrl->getPort());
    auto c = connMgr->get(key);
    HttpResponse response = nullptr;
    while(1) {
        if(c == nullptr) {
            if(formerUrl != nullptr) {
                //close former connection;
                close(formerUrl);
            }

            c = createHttpConnection(mCurrentUrl,option);
            connMgr->add(key,c);
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

void _HttpClient::close(HttpUrl url) {
    auto u = (url==nullptr)?mCurrentUrl:url;

    if(u != nullptr) {
        HttpClientConnKey key = createHttpClientConnKey(u->getScheme(),
                                                        u->getHost(),
                                                        u->getPath(),
                                                        u->getPort());
        auto c = connMgr->get(key);
        if(c != nullptr) {
            c->close();
            connMgr->remove(key);
        }
    }
}


}

