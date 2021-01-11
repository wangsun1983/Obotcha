#ifndef __OBOTCHA_HTTP_REQUEST_HPP__
#define __OBOTCHA_HTTP_REQUEST_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "HttpPacket.hpp"
#include "HttpUrl.hpp"
#include "HttpMultiPart.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpRequest) {

public:
    friend class _HttpRequestWriter;
    _HttpRequest(int,HttpUrl);

    void setHeader(String,String);
    void setEntity(String);

    void setVersion(int,int);

    int getMajorVer();
    int getMinorVer();

    void setMajorVer(int);
    void setMinorVer(int);

    void setMethod(int);
    int getMethod();

    void addMultiPartContent(HttpMultiPartContent);
    void addMultiPartFile(HttpMultiPartFile);

    String getHeader(String);
    String getEntity();

    HttpUrl getUrl();
    
private:
    HttpUrl mUrl;
    HttpPacket mPacket;
    int mMethod;
    
};

}

#endif
