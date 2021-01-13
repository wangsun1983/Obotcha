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
   static const String LineEnd;
   static const String ChunkEnd;
   static const String BoundaryTag;
   static const String BoundarySeperator;
   static const String BoundaryBeginning;
   static const String PartName;
   static const String PartFileName;
   static const String ContentSpace;
   static const String ContentHttp;
};

}
#endif
