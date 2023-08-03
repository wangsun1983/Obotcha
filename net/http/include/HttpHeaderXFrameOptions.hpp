#ifndef __OBOTCHA_HTTP_X_FRAME_OPTIONS_HPP__
#define __OBOTCHA_HTTP_X_FRAME_OPTIONS_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderXFrameOptions) {

public:
    _HttpHeaderXFrameOptions() = default;
    explicit _HttpHeaderXFrameOptions(String);

    void load(String);

    String toString() override;

    String option;
    String uri;
};

}
#endif
