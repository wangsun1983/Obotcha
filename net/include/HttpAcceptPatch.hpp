#ifndef __OBOTCHA_HTTP_ACCEPT_PATCH_HPP__
#define __OBOTCHA_HTTP_ACCEPT_PATCH_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpAcceptPatchItem) {
public:
    _HttpAcceptPatchItem(String t,String c);
    String type;
    String charset;
};

DECLARE_CLASS(HttpAcceptPatch) {

public:
    _HttpAcceptPatch();
    _HttpAcceptPatch(String);

    void import(String);

    ArrayList<HttpAcceptPatchItem> get();
    void add(String type,String charset);

    String toString();

private:
    ArrayList<HttpAcceptPatchItem> patches;
};

}
#endif
