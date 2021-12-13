#include "Http2GoAwayFrame.hpp"

namespace obotcha {

void _Http2GoAwayFrame::import(ByteArray) {
    //TODO
}

ByteArray _Http2GoAwayFrame::toByteArray() {
    //TODO
}

uint32_t _Http2GoAwayFrame::getLastStreamId() {
    return lastStreamId;
}

void _Http2GoAwayFrame::setLastStreamId(uint32_t v) {
    lastStreamId = v;
}

uint32_t _Http2GoAwayFrame::getErrorCode() {
    return errorCode;
}

void _Http2GoAwayFrame::setErrorCode(uint32_t e) {
    errorCode = e; 
}

}
