#include "HttpHeaderRange.hpp"
#include "StringBuffer.hpp"
#include "ForEveryOne.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpHeaderRangeItem::_HttpHeaderRangeItem(int start,int end):rangeStart(start),rangeEnd(end) {
}

_HttpHeaderRange::_HttpHeaderRange(String s) {
    load(s->trim());
}

void _HttpHeaderRange::jumpSpace(const char *p,size_t &i,size_t size) const {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpHeaderRange::load(String s) {
    const char *p = s->toChars();
    size_t size = s->size();
    size_t start = 0;
    int status = ParseUinit;
    
    ranges->clear();

    HttpHeaderRangeItem item = nullptr;
    for(size_t i = 0;i < size;i++) {
        if(p[i] == '='||p[i] == ',' || p[i] == '-' || i == size - 1) {
            switch(status) {
                case ParseUinit: {
                    if(p[i] == '=') {
                        this->unit = String::New(p,start,i-start);
                        i = i+1;
                        jumpSpace(p,i,size);
                        start = i;
                        status = ParseRangeStart;
                    }
                }
                break;

                case ParseRangeStart: {
                    if(p[i] == '-') {
                        int startInt = String::New(p,start,i-start)->toBasicInt();
                        item = HttpHeaderRangeItem::New();
                        item->rangeStart = startInt;
                        i++;
                        jumpSpace(p,i,size);
                        
                        if(i == size) {
                            //no end 
                            item->rangeEnd = -1;
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
                        int endInt = String::New(p,start,i-start)->toBasicInt();
                        item->rangeEnd = endInt;
                        ranges->add(item);
                        i++;
                        jumpSpace(p,i,size);
                        start = i;
                        status = ParseRangeStart;
                    }
                break;

                default:
                    LOG(ERROR)<<"HttpHeaderRange,load unknow type:"<<status;
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
    ranges->add(HttpHeaderRangeItem::New(start,end));
}

void _HttpHeaderRange::setRanges(ArrayList<HttpHeaderRangeItem> l) {
    ranges = l;
}

String _HttpHeaderRange::toString() {
    StringBuffer range = StringBuffer::New();
    if(unit != nullptr) {
        range->append(unit,"=");
    }

    ForEveryOne(item,ranges) {
        range->append(String::New(item->rangeStart));
        if(item->rangeEnd == -1) {
            range->append("-, ");
        } else {
            range->append("-",String::New(item->rangeEnd),", ");
        }
    }
    return range->toString(0,range->size() - 2);
}

}
