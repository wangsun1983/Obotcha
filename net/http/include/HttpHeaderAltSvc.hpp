#ifndef __OBOTCHA_HTTP_HEADER_ALT_SVC_HPP__
#define __OBOTCHA_HTTP_HEADER_ALT_SVC_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "HttpUrl.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAltSvcServiceItem) {
public:
    _HttpHeaderAltSvcServiceItem(String,HttpUrl);
    String serviceName;
    HttpUrl url;
};

DECLARE_CLASS(HttpHeaderAltSvc) {

public:
    _HttpHeaderAltSvc();
    explicit _HttpHeaderAltSvc(String);

    void load(String);

    void addService(String,HttpUrl);
    void setMaxAge(int);
    void setPersist(int);

    ArrayList<HttpHeaderAltSvcServiceItem> getServices();
    int getMaxAge() const;
    int getPersist() const;

    String toString();

private:
    ArrayList<HttpHeaderAltSvcServiceItem> altSvcs;
    int maxAge;
    int persist;
};

}
#endif
