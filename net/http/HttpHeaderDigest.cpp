#include "HttpHeaderDigest.hpp"
#include "HttpHeaderContentParser.hpp"
#include "Math.hpp"

namespace obotcha {

_HttpHeaderDigestItem::_HttpHeaderDigestItem(String alg,String v) {
    algorithm = alg;
    value = v;
}

_HttpHeaderDigest::_HttpHeaderDigest() {
    digests = createArrayList<HttpHeaderDigestItem>();
}

_HttpHeaderDigest::_HttpHeaderDigest(String s) {
    import(s);
}

void _HttpHeaderDigest::import(String s) {
    st(HttpHeaderContentParser)::import(s,[this](String directive,String parameter) {
        digests->add(createHttpHeaderDigestItem(directive,parameter));
    });
}

ArrayList<HttpHeaderDigestItem> _HttpHeaderDigest::getDigests() {
    return digests;
}

String _HttpHeaderDigest::toString() {
    String digest = "";
    auto iterator = digests->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderDigestItem item = iterator->getValue();
        digest->append(item->algorithm,"=",item->value,",");
    }

    return digest->subString(0,digest->size() - 1);
}

}
