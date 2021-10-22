#ifndef __OBOTCHA_HTTP_TRANSFER_ENCODING_HPP__
#define __OBOTCHA_HTTP_TRANSFER_ENCODING_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpTransferEncoding) {

public:
    _HttpTransferEncoding();
    _HttpTransferEncoding(String);

    void import(String);

    ArrayList<String> get();
    void add(String);

    String toString();

private:
    ArrayList<String> encodings;
};

}
#endif
