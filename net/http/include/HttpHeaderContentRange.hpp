#ifndef __OBOTCHA_HTTP_CONTENT_RANGE_HPP__
#define __OBOTCHA_HTTP_CONTENT_RANGE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentRange) {

public:
    _HttpHeaderContentRange();
    _HttpHeaderContentRange(String);

    void import(String);

    String getUnit();
    int getStart();
    int getEnd();
    int getSize();

    void setUnit(String);
    void setStart(int);
    void setEnd(int);
    void setSize(int);

    String toString();

private:
    enum {
        ParseUnit = 0,
        ParseStart,
        ParseEnd,
        ParseSize
    };

    String mUnit;
    int mStart;
    int mEnd;
    int mSize;
};

}
#endif
