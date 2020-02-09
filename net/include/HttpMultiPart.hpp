#ifndef __HTTP_MULIT_PART_HPP__
#define __HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "TcpClient.hpp"
#include "HttpUrl.hpp"
#include "File.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMultiPartFile) {

public:
    //TODO

private:
    File mFile;

}; 

DECLARE_SIMPLE_CLASS(HttpMultiPart) {

public:
    _HttpMultiPart();

    int getNextPartType();

    HttpMultiPartFile getNextPartFile();

    const static int MultiPartFile;

private:
    int mFd;

    HttpHeader mHeader;
    
    
};

}
#endif
