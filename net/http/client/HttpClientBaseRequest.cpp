#include "HttpClientBaseRequest.hpp"

namespace obotcha {


_HttpClientBaseRequest::_HttpClientBaseRequest(String url) {
    mUrl = createHttpUrl(url);
}

HttpUrl _HttpClientBaseRequest::getUrl() {
    return mUrl;
}


}
