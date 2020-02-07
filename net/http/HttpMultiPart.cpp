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


const int _HttpMultiPart::MultiPartFile = 1;

_HttpMultiPart::_HttpMultiPart() {

}

int _HttpMultiPart::getNextPartType() {

}

HttpMultiPartFile _HttpMultiPart::getNextPartFile() {

}
