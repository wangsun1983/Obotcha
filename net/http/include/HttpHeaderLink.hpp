#ifndef __OBOTCHA_HTTP_HEADER_LINK_HPP__
#define __OBOTCHA_HTTP_HEADER_LINK_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderLink) {

public:
    _HttpHeaderLink() = default;
    explicit _HttpHeaderLink(String);

    String toString() override;

    String rel;
    String anchor;
    String rev;
    String hreflag;
    String media;
    String title;
    String titleext;
    String url;

private:
    void load(String);
};

}
#endif
