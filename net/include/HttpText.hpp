#ifndef __OBOTCHA_HTTP_TEXT_HPP__
#define __OBOTCHA_HTTP_TEXT_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "File.hpp"
#include "HttpHeader.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpText) {

public:
   //static const String LineEnd;
   //static const String DoubleLineEnd;
   static const String HttpEnd;
   static const String Boundary;
   static const String BoundarySeperator;
   static const String BoundaryBeginning;
   static const String MultiPartFileName;
   static const String MultiPartName;
   static const String MultiPartEnd;
   static const String CRLF;
   static const String CR;
   static const String LF;
   
   //static const String PartName;
   //static const String PartFileName;
   static const String ContentSpace;
   static const String ContentHttp;
};

}
#endif
