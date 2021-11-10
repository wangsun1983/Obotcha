#include "HttpHeaderRange.hpp"

namespace obotcha {

_HttpHeaderRangeItem::_HttpHeaderRangeItem(int start,int end) {
    this->start = start;
    this->end = end;
}

_HttpHeaderRangeItem::_HttpHeaderRangeItem() {

}

_HttpHeaderRange::_HttpHeaderRange() {
    ranges = createArrayList<HttpHeaderRangeItem>();
}

_HttpHeaderRange::_HttpHeaderRange(String s) {
    import(s->trim());
}

void _HttpHeaderRange::jumpSpace(const char *p,int &i,int size) {
    while(p[i] == ' ' && i < size && p[i] != ';') {
        i++;
    }
}

void _HttpHeaderRange::import(String s) {
    const char *p = s->toChars();
    int size = s->size();
    int start = 0;
    int status = ParseUinit;
    
    HttpHeaderRangeItem item = nullptr;
    printf("start import \n");
    for(int i = 0;i < size;i++) {
        printf("start import trace p is %c\n",p[i]);
        if(p[i] == '='||p[i] == ',' || p[i] == '-' || i == size - 1) {
            switch(status) {
                case ParseUinit: {
                    if(p[i] == '=') {
                        this->unit = createString(p,start,i-start);
                        printf("unit is %s \n",unit->toChars());
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
                        printf("start is %d \n",item->start);
                        i++;
                        jumpSpace(p,i,size);
                        
                        printf("i is %d,size is %d \n",i,size);
                        if(i == size) {
                            //no end 
                            item->end = -1;
                            printf("trace1 end is %d \n",item->end);
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
                        printf("trace2 end is %d \n",item->start);
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
    String range = unit->append("=");
    auto iterator = ranges->getIterator();
    while(iterator->hasValue()) {
        HttpHeaderRangeItem item = iterator->getValue();
        if(item->end == -1) {
            range = range->append(createString(item->start),"-, ");
        } else {
            range = range->append(createString(item->start),"-",createString(item->end),", ");
        }
        iterator->next();
    }

    return range->subString(0,range->size() - 2);
}

}
