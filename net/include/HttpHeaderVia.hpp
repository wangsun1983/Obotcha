#ifndef __OBOTCHA_HTTP_HEADER_VIA_HPP__
#define __OBOTCHA_HTTP_HEADER_VIA_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderViaItem) {
public:
    String protocol;
    String version;
    HttpUrl url;
    String pseudonym;
};

DECLARE_CLASS(HttpHeaderVia) {

public:
    _HttpHeaderVia();
    _HttpHeaderVia(String);

    void import(String);

    ArrayList<HttpHeaderViaItem> get();
    void add(HttpHeaderViaItem);

    String toString();

private:
    enum {
        ParseVersion = 0,
        ParseDect,
        ParseUrl,
        ParsePseudonym
    };

    void jumpSpace(const char *p,int &i,int size);

    ArrayList<HttpHeaderViaItem> vias;
};

}
#endif
