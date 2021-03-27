#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "HashMap.hpp"
#include "HttpCookie.hpp"
#include "HttpUrl.hpp"
#include "File.hpp"
#include "HttpHeader.hpp"
#include "HttpFile.hpp"
#include "KeyValuePair.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpMultiPartFile) {

public:
    _HttpMultiPartFile(File);
    _HttpMultiPartFile(HttpFile);

    HttpFile getHttpFile();

private:
    HttpFile mFile;
};

DECLARE_SIMPLE_CLASS(HttpMultiPart) {
public:
    _HttpMultiPart();
    ArrayList<HttpMultiPartFile> files;
    ArrayList<KeyValuePair<String,String>>contents;
};

}
#endif
