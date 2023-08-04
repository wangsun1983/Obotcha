#ifndef __OBOTCHA_HTTP_HEADER_RANGE_HPP__
#define __OBOTCHA_HTTP_HEADER_RANGE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderRangeItem) {
public:
    _HttpHeaderRangeItem() = default;
    _HttpHeaderRangeItem(int,int);
    int rangeStart;
    int rangeEnd;
};

DECLARE_CLASS(HttpHeaderRange) {

public:
    _HttpHeaderRange();
    explicit _HttpHeaderRange(String);

    void load(String);

    ArrayList<HttpHeaderRangeItem> getRanges();
    String getUnit();
    
    void setUnit(String);
    void addRange(int start,int end);
    void setRanges(ArrayList<HttpHeaderRangeItem>);

    String toString() override;

private:
    enum Status {
        ParseUinit = 0,
        ParseRangeStart,
        ParseRangeEnd
    };

    void jumpSpace(const char *p,size_t &i,size_t size);

    String unit;
    ArrayList<HttpHeaderRangeItem> ranges;
};

}
#endif
