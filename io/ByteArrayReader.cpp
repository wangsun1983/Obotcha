/**
 * @file ByteArrayReader.cpp
 * @brief  Provides low-level read access to a byte[] array.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
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
