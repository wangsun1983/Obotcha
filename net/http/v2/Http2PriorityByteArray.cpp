#include "Http2PriorityByteArray.hpp"

namespace obotcha {

_Http2PriorityByteArray::_Http2PriorityByteArray(int size):_ByteArray(size) {

}

void _Http2PriorityByteArray::setPriorityWeight(int p) {
    priority = p;
}

int _Http2PriorityByteArray::getPriorityWeight() {
    return priority;
}


}
