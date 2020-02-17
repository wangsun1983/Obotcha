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

DECLARE_SIMPLE_CLASS(HttpMultiPartData) {
public:
    static const int PartFile;
    static const int PartBlock;

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
    int mType;
};

DECLARE_SIMPLE_CLASS(HttpMultiPartBlock) EXTENDS(HttpMultiPartData){

public:
    _HttpMultiPartBlock(ByteArray);

    ByteArray getBlockData();

private:
    ByteArray mBuff;
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
