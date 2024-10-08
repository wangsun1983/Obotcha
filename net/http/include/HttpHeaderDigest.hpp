#ifndef __OBOTCHA_HTTP_DIGEST_HEADER_HPP__
#define __OBOTCHA_HTTP_DIGEST_HEADER_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderDigestItem) {
public:
    _HttpHeaderDigestItem(String,String);
    //Permitted digest algorithms values include: unixsum, unixcksum, 
    //crc32c, sha-256 and sha-512, id-sha-256, id-sha-512
    String algorithm;
    String value;
};

DECLARE_CLASS(HttpHeaderDigest) {

public:
    _HttpHeaderDigest() = default;
    explicit _HttpHeaderDigest(String);

    void load(String);

    ArrayList<HttpHeaderDigestItem> getDigests();
    void add(String,String);

    String toString() override;

private:
    ArrayList<HttpHeaderDigestItem> digests = ArrayList<HttpHeaderDigestItem>::New();
};

}
#endif
