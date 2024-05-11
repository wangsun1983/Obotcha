#ifndef __OBOTCHA_HTTP_HEADER_SERVER_TIMING_HPP__
#define __OBOTCHA_HTTP_HEADER_SERVER_TIMING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderServerTimingItem) {
public:
    _HttpHeaderServerTimingItem() = default;
    String name = nullptr;
    String dur = nullptr;
    String desc = nullptr;
};

DECLARE_CLASS(HttpHeaderServerTiming) {

public:
    _HttpHeaderServerTiming() = default;
    explicit _HttpHeaderServerTiming(String);

    void load(String);

    void add(String name,String dur,String desc);

    ArrayList<HttpHeaderServerTimingItem> get();

    String toString() override;

private:
    ArrayList<HttpHeaderServerTimingItem> lists = ArrayList<HttpHeaderServerTimingItem>::New();
};

}
#endif
