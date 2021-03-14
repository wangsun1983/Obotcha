#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "http_parser.h"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "File.hpp"
#include "HttpMultiPart.hpp"

using namespace obotcha;

//_HttpMultiPart();
_HttpMultiPart::_HttpMultiPart() {
    files = createArrayList<HttpMultiPartFile>();
    contents = createArrayList<KeyValuePair<String,String>>();
}

//-----------------HttpMultiPartFile-----------------
_HttpMultiPartFile::_HttpMultiPartFile(HttpFile f):mFile(f){
}

_HttpMultiPartFile::_HttpMultiPartFile(File f){
    mFile = createHttpFile(f);
}

HttpFile _HttpMultiPartFile::getHttpFile() {
    return mFile;
}
