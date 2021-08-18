#ifndef __OBOTCHA_HTTP_RESPONSE_ENTITY_HPP__
#define __OBOTCHA_HTTP_RESPONSE_ENTITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "TextContent.hpp"
#include "HttpStatus.hpp"
#include "HttpCookie.hpp"

namespace obotcha {

DECLARE_CLASS(HttpResponseEntity) {

public:
    template<typename U>
    _HttpResponseEntity(U v,int status = st(HttpStatus)::Ok,ArrayList<HttpCookie> cookies = nullptr) {
        mContent = createTextContent(v);
        mStatus = status;
        mCookies = cookies;
    }

    int getStatus();
    TextContent getContent();
    ArrayList<HttpCookie> getCookies();

private:
    int mStatus;
    TextContent mContent;
    ArrayList<HttpCookie> mCookies;
};

}
#endif
