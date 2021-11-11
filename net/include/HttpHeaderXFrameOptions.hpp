#ifndef __OBOTCHA_HTTP_X_FRAME_OPTIONS_HPP__
#define __OBOTCHA_HTTP_X_FRAME_OPTIONS_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {


DECLARE_CLASS(HttpHeaderXFrameOptions) {

public:
    _HttpHeaderXFrameOptions();
    _HttpHeaderXFrameOptions(String);

    void import(String);

    String toString();

    String option;
    String uri;
};

}
#endif
