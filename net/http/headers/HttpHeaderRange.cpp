#include "HttpHeaderRange.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_HttpHeaderRangeItem::_HttpHeaderRangeItem(int start,int end) {
    this->start = start;
    this->end = end;
}

_HttpHeaderRange::_HttpHeaderRange() {
    ranges = createArrayList<HttpHeaderRangeItem>();
}

_HttpHeaderRange::_HttpHeaderRange(String s) {
    load(s->trim());
}

void _HttpHeaderRange::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpHeaderRange::load(String s) {
    const char *p = s->toChars();
    int size = s->size();
    int start = 0;
    int status = ParseUinit;
    
    ranges->clear();

    HttpHeaderRangeItem item = nullptr;
    for(int i = 0;i < size;i++) {
        if(p[i] == '='||p[i] == ',' || p[i] == '-' || i == size - 1) {
            switch(status) {
                case ParseUinit: {
                    if(p[i] == '=') {
                        this->unit = createString(p,start,i-start);
                        i = i+1;
                        jumpSpace(p,i,size);
                        start = i;
                        status = ParseRangeStart;
                    }
                }
                break;

                case ParseRangeStart: {
                    if(p[i] == '-') {
                        int startInt = createString(p,start,i-start)->toBasicInt();
                        item = createHttpHeaderRangeItem();
                        item->start = startInt;
                        i++;
                        jumpSpace(p,i,size);
                        
                        if(i == size) {
                            //no end 
                            item->end = -1;
                            ranges->add(item);
                            return;
                        }

                        start = i;
                        status = ParseRangeEnd;
                    }
                }
                break;

                case ParseRangeEnd:
                    if(p[i] == ',' ||i == size - 1) {
                        int endInt = createString(p,start,i-start)->toBasicInt();
                        item->end = endInt;
                        ranges->add(item);
                        i++;
                        jumpSpace(p,i,size);
                        start = i;
                        status = ParseRangeStart;
                    }
                break;
            }
        }
    }
}

ArrayList<HttpHeaderRangeItem> _HttpHeaderRange::getRanges() {
    return ranges;
}

String _HttpHeaderRange::getUnit() {
    return unit;
}

void _HttpHeaderRange::setUnit(String s) {
    unit = s->trim();
}

void _HttpHeaderRange::addRange(int start,int end) {
    ranges->add(createHttpHeaderRangeItem(start,end));
}

void _HttpHeaderRange::setRanges(ArrayList<HttpHeaderRangeItem> l) {
    ranges = l;
}

String _HttpHeaderRange::toString() {
    StringBuffer range = createStringBuffer();
    if(unit != nullptr) {
        range->append(unit,"=");
    }

    ForEveryOne(item,ranges) {
        range->append(createString(item->start));
        if(item->end == -1) {
            range->append("-, ");
        } else {
            range->append("-",createString(item->end),", ");
        }
    }
    return range->toString(0,range->size() - 2);
}

}
