#include "HttpContentRange.hpp"

namespace obotcha {

_HttpContentRange::_HttpContentRange() {
    mUnit = nullptr;
    mStart = -1;
    mEnd = -1;
    mSize = -1;
}

_HttpContentRange::_HttpContentRange(String s):_HttpContentRange() {
    import(s);
}

void _HttpContentRange::import(String s) {
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

String _HttpContentRange::getUnit() {
    return mUnit;
}

int _HttpContentRange::getStart() {
    return mStart;
}

int _HttpContentRange::getEnd() {
    return mEnd;
}

int _HttpContentRange::getSize() {
    return mSize;
}

void _HttpContentRange::setUnit(String s) {
    mUnit = s->trim();
}

void _HttpContentRange::setStart(int s) {
    mStart = s;
}

void _HttpContentRange::setEnd(int s) {
    mEnd = s;
}

void _HttpContentRange::setSize(int s) {
    mSize = s;
}

String _HttpContentRange::toString() {
    return mUnit->append(" ",createString(mStart),"-",createString(mEnd),"/",createString(mSize));
}

}