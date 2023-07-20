#ifndef __OBOTCHA_HTTP_HEADER_ACCEPT_PATCH_HPP__
#define __OBOTCHA_HTTP_HEADER_ACCEPT_PATCH_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderAcceptPatchItem) {
public:
    _HttpHeaderAcceptPatchItem(String t,String c);
    String type;
    String charset;
};

DECLARE_CLASS(HttpHeaderAcceptPatch) {

public:
    _HttpHeaderAcceptPatch();
    _HttpHeaderAcceptPatch(String);

    void load(String);

    ArrayList<HttpHeaderAcceptPatchItem> get();
    void add(String type,String charset);

    String toString();

private:
    ArrayList<HttpHeaderAcceptPatchItem> patches;
};

}
#endif
