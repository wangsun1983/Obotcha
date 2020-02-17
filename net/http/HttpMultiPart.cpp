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
const int _HttpMultiPartData::PartFile = 1;
const int _HttpMultiPartData::PartBlock = 1;

int _HttpMultiPartData::getType() {
    return mType;
}

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartFile::_HttpMultiPartFile(File f):mFile(f),mType(PartFile) {
    
}

_HttpMultiPartFile::_HttpMultiPartFile(String path) {
    mFile = createFile(path);
}

File _HttpMultiPartFile::getFile() {
    return mFile;
}

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartBlock::_HttpMultiPartBlock(ByteArray data):mBuff(data) {

}

ByteArray _HttpMultiPartBlock::getBlockData() {
    return mBuff;
}

//-----------------HttpMultiPart-----------------
_HttpMultiPart::_HttpMultiPart() {

}

ArrayList<HttpMultiPartData> _HttpMultiPart::getDatas() {
    return mDatas;
}

void _HttpMultiPart::addPartData(HttpMultiPartData data) {
    mDatas->add(data);
}