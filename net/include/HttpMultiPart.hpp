#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpFile.hpp"
#include "HttpHeader.hpp"
#include "HttpUrl.hpp"
#include "KeyValuePair.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartFile) {

  public:
    _HttpMultiPartFile(File);
    _HttpMultiPartFile(HttpFile);

    HttpFile getHttpFile();

  private:
    HttpFile mFile;
};

DECLARE_CLASS(HttpMultiPart) {
  public:
    _HttpMultiPart();
    ArrayList<HttpMultiPartFile> files;
    ArrayList<KeyValuePair<String, String>> contents;
};

} // namespace obotcha
#endif
