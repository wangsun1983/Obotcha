#include "HttpHeaderDigest.hpp"
#include "HttpHeaderContentParser.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderDigestItem::_HttpHeaderDigestItem(String alg,String v):algorithm(alg),value(v) {
}

_HttpHeaderDigest::_HttpHeaderDigest(String s) {
    load(s);
}

void _HttpHeaderDigest::load(String s) {
    digests->clear();

    st(HttpHeaderContentParser)::load(s,[this](String directive,String parameter) {
        digests->add(HttpHeaderDigestItem::New(directive,parameter));
    });
}

ArrayList<HttpHeaderDigestItem> _HttpHeaderDigest::getDigests() {
    return digests;
}

void _HttpHeaderDigest::add(String algorithm,String value) {
    digests->add(HttpHeaderDigestItem::New(algorithm->trim(),value->trim()));
}

String _HttpHeaderDigest::toString() {
    StringBuffer digest = StringBuffer::New();
    ForEveryOne(item,digests) {
        digest->append(item->algorithm,"=",item->value,",");
    }
    return digest->toString(0,digest->size() - 1);
}

}
