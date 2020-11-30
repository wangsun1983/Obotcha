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

//_HttpMultiPart();
_HttpMultiPart::_HttpMultiPart() {
    files = createArrayList<HttpMultiPartFile>();
    contents = createArrayList<HttpMultiPartContent>();
}

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartFile::_HttpMultiPartFile(File f):mFile(f){
}

_HttpMultiPartFile::_HttpMultiPartFile(String path) {
    mFile = createFile(path);
}

File _HttpMultiPartFile::getFile() {
    return mFile;
}

//-----------------HttpMultiPartContent-----------------

_HttpMultiPartContent::_HttpMultiPartContent(String name,String data):mName(name),mValue(data){

}

String _HttpMultiPartContent::getName() {
    return mName;
}

String _HttpMultiPartContent::getValue() {
    return mValue;
}
