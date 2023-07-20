#include "HttpHeaderContentRange.hpp"

namespace obotcha {

_HttpHeaderContentRange::_HttpHeaderContentRange() {
    mUnit = nullptr;
    mStart = -1;
    mEnd = -1;
    mSize = -1;
}

_HttpHeaderContentRange::_HttpHeaderContentRange(String s):_HttpHeaderContentRange() {
    load(s);
}

void _HttpHeaderContentRange::load(String s) {
    String value = s->trim();
    const char *p = value->toChars();

    int status = ParseUnit;
    int start = 0;
    int size = value->size();

    for(int i = 0;i<size;i++) {
        if(p[i] == ' ' || p[i] == '-' || p[i] == '/') {
            switch(status) {
                case ParseUnit:
                this->mUnit = createString(p,start,i-start);
                status = ParseStart;
                start = i+1;
                break;

                case ParseStart:
                this->mStart = createString(p,start,i-start)->toBasicInt();
                status = ParseEnd;
                start = i+1;
                break;

                case ParseEnd:
                this->mEnd = createString(p,start,i-start)->toBasicInt();
                status = ParseSize;
                start = i+1;
                break;

                case ParseSize:
                this->mSize = createString(p,start,i-start)->toBasicInt();
                return;
            }
        }
    }
    
    mSize = createString(p,start,size-start)->toBasicInt();
}

String _HttpHeaderContentRange::getUnit() {
    return mUnit;
}

int _HttpHeaderContentRange::getStart() {
    return mStart;
}

int _HttpHeaderContentRange::getEnd() {
    return mEnd;
}

int _HttpHeaderContentRange::getSize() {
    return mSize;
}

void _HttpHeaderContentRange::setUnit(String s) {
    mUnit = s->trim();
}

void _HttpHeaderContentRange::setStart(int s) {
    mStart = s;
}

void _HttpHeaderContentRange::setEnd(int s) {
    mEnd = s;
}

void _HttpHeaderContentRange::setSize(int s) {
    mSize = s;
}

String _HttpHeaderContentRange::toString() {
    return mUnit->append(" ",createString(mStart),"-",createString(mEnd),"/",createString(mSize));
}

}