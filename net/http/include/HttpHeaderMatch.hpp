#ifndef __OBOTCHA_HTTP_HEADER_MATCH_HPP__
#define __OBOTCHA_HTTP_HEADER_MATCH_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderMatchItem) {
public:
    _HttpHeaderMatchItem(String,bool);
    bool isWeakAlg;
    String tag;
};

DECLARE_CLASS(HttpHeaderMatch) {

public:
    _HttpHeaderMatch() = default;
    explicit _HttpHeaderMatch(String);

    void load(String);

    ArrayList<HttpHeaderMatchItem> get() const;
    void add(String,bool isWeak = false);

    String toString() override;

private:
    ArrayList<HttpHeaderMatchItem> items = ArrayList<HttpHeaderMatchItem>::New();
    String _convertTag(String) const;
};

}
#endif
