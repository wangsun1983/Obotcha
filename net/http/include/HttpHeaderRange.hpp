#ifndef __OBOTCHA_HTTP_HEADER_RANGE_HPP__
#define __OBOTCHA_HTTP_HEADER_RANGE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderRangeItem) {
public:
    _HttpHeaderRangeItem();
    _HttpHeaderRangeItem(int,int);
    int start;
    int end;
};

DECLARE_CLASS(HttpHeaderRange) {

public:
    _HttpHeaderRange();
    _HttpHeaderRange(String);

    void import(String);

    ArrayList<HttpHeaderRangeItem> getRanges();
    String getUnit();
    
    void setUnit(String);
    void addRange(int start,int end);
    void setRanges(ArrayList<HttpHeaderRangeItem>);

    String toString();

private:
    enum Status {
        ParseUinit = 0,
        ParseRangeStart,
        ParseRangeEnd
    };

    void jumpSpace(const char *p,int &i,int size);

    String unit;
    ArrayList<HttpHeaderRangeItem> ranges;
};

}
#endif
