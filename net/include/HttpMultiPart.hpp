#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "HashMap.hpp"
#include "HttpHeader.hpp"
#include "HttpUrl.hpp"
#include "Pair.hpp"
#include "String.hpp"
#include "File.hpp"
#include "HttpHeaderContentType.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartFile) {

public:
    _HttpMultiPartFile(String filename,String name = nullptr,HttpHeaderContentType contentType = nullptr);
    _HttpMultiPartFile(File filename,String name = nullptr);
    //String getKey();
    //File getFile();
    //String getFileName();

    String getName();
    String getOriginalFileName();
    HttpHeaderContentType getContentType();
    File getFile();

private:
    File mFile;
    String mName;
    String mOriginalFileName;
    HttpHeaderContentType mContentType;
};

DECLARE_CLASS(HttpMultiPart) {
public:
    _HttpMultiPart();
    ArrayList<HttpMultiPartFile> files;
    ArrayList<Pair<String, String>> contents;
    String getBoundary();
    long getContentLength();

private:
    String mBoundary;
};

} // namespace obotcha
#endif
