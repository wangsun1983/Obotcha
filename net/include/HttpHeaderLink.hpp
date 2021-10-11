#ifndef __OBOTCHA_HTTP_HEADER_LINK_HPP__
#define __OBOTCHA_HTTP_HEADER_LINK_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HashMap.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLink) {

public:
    _HttpHeaderLink();
    _HttpHeaderLink(String);

    String toString();

    String rel;
    String anchor;
    String rev;
    String hreflag;
    String media;
    String title;
    String titleext;
    String url;

private:
    void import(String);
};

}
#endif
