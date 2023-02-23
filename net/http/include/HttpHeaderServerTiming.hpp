#ifndef __OBOTCHA_HTTP_HEADER_SERVER_TIMING_HPP__
#define __OBOTCHA_HTTP_HEADER_SERVER_TIMING_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderServerTimingItem) {
public:
    _HttpHeaderServerTimingItem();
    String name;
    String dur;
    String desc;
};

DECLARE_CLASS(HttpHeaderServerTiming) {

public:
    _HttpHeaderServerTiming();
    _HttpHeaderServerTiming(String);

    void import(String);

    //void add(HttpHeaderServerTimingItem);
    void add(String name,String dur,String desc);

    ArrayList<HttpHeaderServerTimingItem> get();

    String toString();

private:
    ArrayList<HttpHeaderServerTimingItem> lists;
};

}
#endif
