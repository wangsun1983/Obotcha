#ifndef __OBOTCHA_HTTP_HEADER_LINK_HPP__
#define __OBOTCHA_HTTP_HEADER_LINK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLink) {

public:
    _HttpHeaderLink();
    _HttpHeaderLink(String);

    void setUrl(String);
    void setProp(String,String);

    String getUrl();
    String getProp(String);

private:
    String mUrl;
    HashMap<String,String> mProps;
};

}
#endif
