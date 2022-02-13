#include "HttpBaseRequest.hpp"

namespace obotcha {

void _HttpBaseRequest::setUrl(HttpUrl url) {
    mUrl = url;
}

void _HttpBaseRequest::setUrl(String url) {
    mUrl = createHttpUrl(url);
}

HttpUrl _HttpBaseRequest::getUrl() {
    return mUrl;
}

}
