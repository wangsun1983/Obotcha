#include "Http2FrameByteArray.hpp"

namespace obotcha {

_Http2FrameByteArray::_Http2FrameByteArray(int size):_ByteArray(size) {

}

_Http2FrameByteArray::_Http2FrameByteArray(Http2FrameByteArray array,int start,int size)
                        :_ByteArray(array->toValue() + start,size) {
    this->priority = array->priority;
    this->type = array->type;
}

void _Http2FrameByteArray::setPriorityWeight(int p) {
    priority = p;
}

int _Http2FrameByteArray::getPriorityWeight() {
    return priority;
}

void _Http2FrameByteArray::setType(int value) {
    type = value;
}

int _Http2FrameByteArray::getType() {
    return type;
}

}
