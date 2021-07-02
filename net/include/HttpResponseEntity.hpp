#ifndef __OBOTCHA_HTTP_RESPONSE_ENTITY_HPP__
#define __OBOTCHA_HTTP_RESPONSE_ENTITY_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "TextContent.hpp"
#include "HttpStatus.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpResponseEntity) {

public:
    template<typename U>
    _HttpResponseEntity(U v,int status) {
        mContent = createTextContent(v);
        mStatus = st(HttpStatus)::Ok;
    }

    template<typename U>
    _HttpResponseEntity(U v) {
        mContent = createTextContent(v);
        mStatus = st(HttpStatus)::Ok;
    }

    int getStatus();
    TextContent getContent();

private:
    int mStatus;
    TextContent mContent;
};

}
#endif
