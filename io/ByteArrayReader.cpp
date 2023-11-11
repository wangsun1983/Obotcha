#include "ByteArrayReader.hpp"
#include "Inspect.hpp"
#include "IllegalArgumentException.hpp"

namespace obotcha {

_ByteArrayReader::_ByteArrayReader(ByteArray data, st(IO)::Endianness endiness):
                                    mData(data),mMode(endiness) {
    mDataPtr = data->toValue();
    mSize = data->size();
}

size_t _ByteArrayReader::read(ByteArray data) {
    Inspect(mIndex >= mSize,-1)
    size_t size = std::min(mSize - mIndex,data->size());
    memcpy(data->toValue(), &mDataPtr[mIndex], size);
    mIndex += size;
    return size;
}

uint64_t _ByteArrayReader::getIndex() {
    return mIndex;
}

uint64_t _ByteArrayReader::getRemainSize() {
    return mSize - mIndex;
}

void _ByteArrayReader::setIndex(uint64_t index) {
    Panic(index >= mSize,IllegalArgumentException,"index is larger than size");
    mIndex = index;
}

bool _ByteArrayReader::isReadable() {
    return mSize > mIndex;
}

} // namespace obotcha
