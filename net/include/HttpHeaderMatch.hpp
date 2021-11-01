#ifndef __OBOTCHA_HTTP_HEADER_MATCH_HPP__
#define __OBOTCHA_HTTP_HEADER_MATCH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

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
    _HttpHeaderMatch();
    _HttpHeaderMatch(String);

    void import(String);

    ArrayList<HttpHeaderMatchItem> get();
    void add(String,bool isWeak = false);

    String toString();

private:
    ArrayList<HttpHeaderMatchItem> items;
    String _convertTag(String);
};

}
#endif
