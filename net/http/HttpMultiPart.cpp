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
#include "HttpMultiPart.hpp"

using namespace obotcha;

//-----------------HttpMultiPartData-----------------
//const int _HttpMultiPartData::PartFile = 1;
//const int _HttpMultiPartData::PartBlock = 2;

int _HttpMultiPartData::getType() {
    return mType;
}

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartFile::_HttpMultiPartFile(File f):mFile(f){
    mType = PartFile;
}

_HttpMultiPartFile::_HttpMultiPartFile(String path) {
    mFile = createFile(path);
    mType = PartFile;
}

File _HttpMultiPartFile::getFile() {
    return mFile;
}

//-----------------HttpMultiPartFile-----------------
const String _HttpMultiPartBlock::TagName = createString("name");

_HttpMultiPartBlock::_HttpMultiPartBlock(String name,String data):mName(name){
    mType = PartBlock;
    mValue = data;
    //mBuff(data),
}

String _HttpMultiPartBlock::getName() {
    return mName;
}

String _HttpMultiPartBlock::getValue() {
    return mValue;
}

//-----------------HttpMultiPart-----------------
_HttpMultiPart::_HttpMultiPart() {
    mDatas = createArrayList<HttpMultiPartData>();
}

ArrayList<HttpMultiPartData> _HttpMultiPart::getDatas() {
    return mDatas;
}

void _HttpMultiPart::addPartData(HttpMultiPartData data) {
    mDatas->add(data);
}