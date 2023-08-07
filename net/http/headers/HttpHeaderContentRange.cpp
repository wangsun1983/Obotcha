#include "HttpHeaderContentRange.hpp"
#include "Log.hpp"

namespace obotcha {

_HttpHeaderContentRange::_HttpHeaderContentRange(String s) {
    load(s);
}

void _HttpHeaderContentRange::load(String s) {
    String value = s->trim();
    const char *p = value->toChars();

    Status status = Status::ParseUnit;
    size_t start = 0;
    size_t size = value->size();

    for(size_t i = 0;i<size;i++) {
        if(p[i] == ' ' || p[i] == '-' || p[i] == '/') {
            switch(status) {
                case Status::ParseUnit:
                    this->mUnit = createString(p,start,i-start);
                    status = Status::ParseStart;
                    start = i+1;
                break;

                case Status::ParseStart:
                    this->mStart = createString(p,start,i-start)->toBasicInt();
                    status = Status::ParseEnd;
                    start = i+1;
                break;

                case Status::ParseEnd:
                    this->mEnd = createString(p,start,i-start)->toBasicInt();
                    status = Status::ParseSize;
                    start = i+1;
                break;

                case Status::ParseSize:
                    this->mSize = createString(p,start,i-start)->toBasicInt();
                return;

                default:
                    LOG(ERROR)<<"HttpHeaderContentRange parse unkonw status:"<<status;
                break;
            }
        }
    }
    
    mSize = createString(p,start,size - start)->toBasicInt();
}

String _HttpHeaderContentRange::getUnit() const {
    return mUnit;
}

int _HttpHeaderContentRange::getStart() const {
    return mStart;
}

int _HttpHeaderContentRange::getEnd() const {
    return mEnd;
}

int _HttpHeaderContentRange::getSize() const {
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