#ifndef __OBOTCHA_HTTP_TEXT_HPP__
#define __OBOTCHA_HTTP_TEXT_HPP__

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

DECLARE_SIMPLE_CLASS(HttpText) {

public:
   static String LineEnd;
   static String BoundaryTag;
   static String BoundarySeperator;
   static String BoundaryBeginning;
   static String PartName;
   static String PartFileName;
};

}
#endif
