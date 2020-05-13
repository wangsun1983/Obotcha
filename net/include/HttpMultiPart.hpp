#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

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

DECLARE_SIMPLE_CLASS(HttpMultiPartData) {
public:
    const static int PartFile = 1;
    const static int PartBlock = 2;

    int getType();

protected:
    int mType;
};

DECLARE_SIMPLE_CLASS(HttpMultiPartFile) EXTENDS(HttpMultiPartData){

public:
    _HttpMultiPartFile(File);

    _HttpMultiPartFile(String);

    File getFile();

private:
    File mFile;
};

DECLARE_SIMPLE_CLASS(HttpMultiPartBlock) EXTENDS(HttpMultiPartData){

public:
    _HttpMultiPartBlock(String,String);

    String getName();

    String getValue();

    const static String TagName;

private:
    String mValue;

    String mName;
};

DECLARE_SIMPLE_CLASS(HttpMultiPart) {

public:
    _HttpMultiPart();

    ArrayList<HttpMultiPartData> getDatas();

    void addPartData(HttpMultiPartData);

private:
    int mFd;

    HttpHeader mHeader;

    ArrayList<HttpMultiPartData> mDatas;

};

}
#endif
