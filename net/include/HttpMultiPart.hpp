#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ArrayList.hpp"
#include "File.hpp"
#include "HashMap.hpp"
#include "HttpHeader.hpp"
#include "HttpUrl.hpp"
#include "KeyValuePair.hpp"
#include "String.hpp"
#include "File.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartFile) {

public:
    _HttpMultiPartFile(String filename,String key = nullptr);
    _HttpMultiPartFile(File filename,String key = nullptr);
    String getKey();
    File getFile();
    String getFileName();

private:
    File mFile;
    String mKey;
    String mFileName;
    String mGenFileName;
};

DECLARE_CLASS(HttpMultiPart) {
public:
    _HttpMultiPart();
    ArrayList<HttpMultiPartFile> files;
    ArrayList<KeyValuePair<String, String>> contents;

    String getBoundary();

    long getContentLength();
private:
    String mBoundary;

};

} // namespace obotcha
#endif
