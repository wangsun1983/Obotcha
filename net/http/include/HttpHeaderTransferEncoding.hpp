#ifndef __OBOTCHA_HTTP_TRANSFER_ENCODING_HPP__
#define __OBOTCHA_HTTP_TRANSFER_ENCODING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderTransferEncoding) {

public:
    _HttpHeaderTransferEncoding() = default;
    explicit _HttpHeaderTransferEncoding(String);

    void load(String);

    ArrayList<String> get() const;
    void add(String);

    String toString();

private:
    ArrayList<String> encodings = createArrayList<String>();
};

}
#endif
