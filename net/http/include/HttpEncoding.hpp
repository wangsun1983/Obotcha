#ifndef __OBOTCHA_HTTP_CONTENT_ENCODING_HPP__
#define __OBOTCHA_HTTP_CONTENT_ENCODING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentEncoding) {

public:
    _HttpHeaderContentEncoding();
    _HttpHeaderContentEncoding(String);
    void load(String);
    ArrayList<String> getEncodings();
    String toString();

private:
    ArrayList<String> encodings;
};

}
#endif
