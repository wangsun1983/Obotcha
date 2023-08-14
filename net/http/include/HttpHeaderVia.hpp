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
    _HttpHeaderVia() = default;
    explicit _HttpHeaderVia(String);

    void load(String);

    ArrayList<HttpHeaderViaItem> get() const;
    void add(String protocol,String version,String url,String pseudonym);
    
    String toString() override;

private:
    enum {
        ParseVersion = 0,
        ParseDect,
        ParseUrl,
        ParsePseudonym
    };

    void jumpSpace(const char *p,size_t &i,size_t size) const;
    ArrayList<HttpHeaderViaItem> vias = createArrayList<HttpHeaderViaItem>();
};

}
#endif
