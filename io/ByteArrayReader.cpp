#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"
#include "Inspect.hpp"
#include "String.hpp"

namespace obotcha {

_ByteArrayReader::_ByteArrayReader(ByteArray data, int mod) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mMode = mod;
}

int _ByteArrayReader::read(ByteArray data) {
    Inspect(mIndex >= mSize,-1);

    int size = std::min(mSize - mIndex,data->size());
    memcpy(data->toValue(), &mDataP[mIndex], size);
    mIndex += size;
    return size;
}

int _ByteArrayReader::getIndex() {
    return mIndex;
}

int _ByteArrayReader::getRemainSize() {
    return mSize - mIndex;
}

void _ByteArrayReader::setIndex(int index) {
    mIndex = index;
}

bool _ByteArrayReader::isReadable() {
    return mSize > mIndex;
}

} // namespace obotcha
