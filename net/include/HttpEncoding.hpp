#ifndef __OBOTCHA_HTTP_CONTENT_ENCODING_HPP__
#define __OBOTCHA_HTTP_CONTENT_ENCODING_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpContentEncoding) {

public:
    _HttpContentEncoding();
    _HttpContentEncoding(String);

    void import(String);

    ArrayList<String> getEncodings();

    String toString();

private:
    ArrayList<String> encodings;
};

}
#endif
