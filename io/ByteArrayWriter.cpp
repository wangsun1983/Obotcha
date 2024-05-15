/**
 * @file ByteArrayWriter.cpp
 * @brief Provides low-level write access to a byte[] array.
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2019-07-12
 * @license none
 */
#include "ByteArrayWriter.hpp"
#include "Inspect.hpp"

namespace obotcha {

const size_t _ByteArrayWriter::DefaultDataSize = 1024;

_ByteArrayWriter::_ByteArrayWriter(st(IO)::Endianness endiness):_ByteArrayWriter(ByteArray::New(DefaultDataSize),endiness) {
    mType = _ByteArrayWriter::Type::Dynamic;
}

_ByteArrayWriter::_ByteArrayWriter(ByteArray data, st(IO)::Endianness endiness):
                                    mData(data),mEndiness(endiness) {
    mDataPtr = data->toValue();
    mSize = data->size();
    mType = _ByteArrayWriter::Type::Regular;
}

void _ByteArrayWriter::reset() {
    mIndex = 0;
}

bool _ByteArrayWriter::preCheck(size_t size) {
    if (getRemainSize() < size) {
        switch(mType) {
            case _ByteArrayWriter::Type::Dynamic:
                mSize = (mData->size() + size)* 7 / 4;
                mData->growTo(mSize);
                mDataPtr = mData->toValue();
                break;
            default:
                return false;
        }
    }
    return true;
}

int _ByteArrayWriter::write(ByteArray data, size_t start,size_t length) {
    Panic(!preCheck(length) || data->isOverflow(start,length),
        ArrayIndexOutOfBoundsException,"write")
    memcpy(&mDataPtr[mIndex], data->toValue() + start, length);
    mIndex += length;
    return length;
}

int _ByteArrayWriter::write(byte *data, size_t length) {
    Panic(!preCheck(length),ArrayIndexOutOfBoundsException,"write")
    memcpy(&mDataPtr[mIndex], data, length);
    mIndex += length;
    return length;
}

int _ByteArrayWriter::write(const char *str,size_t size) {
    size_t writeSize = (size == 0)?strlen(str):size;
    return write((byte *)str,writeSize);
}

size_t _ByteArrayWriter::getIndex() const {
    return mIndex;
}

void _ByteArrayWriter::setIndex(size_t index) {
    Panic(index >= mData->size(),IllegalArgumentException,
        "index is larger than size");
    mIndex = index;
}

size_t _ByteArrayWriter::getRemainSize() const {
    return mData->size() - mIndex;
}

ByteArray _ByteArrayWriter::getByteArray() {
    mData->quickShrink(mIndex);
    return mData;
}

int _ByteArrayWriter::skipBy(size_t length) {
    //Inspect(mIndex + length > mData->size(),-1) 
    Panic(mData->isOverflow(mIndex,length),
            ArrayIndexOutOfBoundsException,"skipBy")
    mIndex += length;
    return 0;
}

} // namespace obotcha
