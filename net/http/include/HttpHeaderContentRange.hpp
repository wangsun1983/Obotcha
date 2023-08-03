#ifndef __OBOTCHA_HTTP_CONTENT_RANGE_HPP__
#define __OBOTCHA_HTTP_CONTENT_RANGE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentRange) {

public:
    _HttpHeaderContentRange() = default;
    explicit _HttpHeaderContentRange(String);

    void load(String);

    String getUnit() const;
    int getStart() const;
    int getEnd() const;
    int getSize() const;

    void setUnit(String);
    void setStart(int);
    void setEnd(int);
    void setSize(int);

    String toString() override;

private:
    enum {
        ParseUnit = 0,
        ParseStart,
        ParseEnd,
        ParseSize
    };

    String mUnit = nullptr;
    int mStart = -1;
    int mEnd = -1;
    int mSize = -1;
};

}
#endif
