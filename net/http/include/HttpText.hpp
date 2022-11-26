#ifndef __OBOTCHA_HTTP_TEXT_HPP__
#define __OBOTCHA_HTTP_TEXT_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpText) {

public:
   static const String HttpEnd;
   static const String Boundary;
   static const String BoundaryBeginning;
   static const String MultiPartFileName;
   static const String MultiPartName;
   static const String MultiPartEnd;
   static const String MultiPartFileTemplate;
   static const String MultiPartContentTemplate;
   static const String MultiPartEndTemplate;

   static const String CRLF;
   static const String CR;
   static const String LF;
   
   static const String ContentSpace;
   static const String ContentHttp;

   static const String HttpChunkEnd;
};

}
#endif
