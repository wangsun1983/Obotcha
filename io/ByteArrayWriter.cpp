/**
 * @file ByteArrayWriter.cpp
 * @brief Byte Array Writer(support Little/Big Endian)
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

_ByteArrayWriter::_ByteArrayWriter(st(IO)::Endianness endiness):_ByteArrayWriter(createByteArray(DefaultDataSize),endiness) {
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
    int needSize = mIndex + size;
    if (mType == _ByteArrayWriter::Type::Dynamic && needSize > mSize) {
        mSize = (mData->size() + size)* 7 / 4;
        mData->growTo(mSize);
        mDataPtr = mData->toValue();
    }
    return mType == _ByteArrayWriter::Type::Dynamic || needSize <= mSize;
}

int _ByteArrayWriter::write(ByteArray data, size_t start,size_t length) {
    Inspect(!preCheck(length) || start + length > data->size(),-1)
    memcpy(&mDataPtr[mIndex], data->toValue() + start, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(byte *data, size_t length) {
    Inspect(!preCheck(length),-1)
    memcpy(&mDataPtr[mIndex], data, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(const char *str,size_t size) {
    size_t writeSize = (size == 0)?strlen(str):size;
    return write((byte *)str,writeSize);
}


int _ByteArrayWriter::getIndex() const {
    return mIndex;
}

void _ByteArrayWriter::setIndex(size_t index) {
    mIndex = index;
}

size_t _ByteArrayWriter::getReminderSize() const {
    return mData->size() - mIndex;
}

ByteArray _ByteArrayWriter::getByteArray() {
    mData->quickShrink(mIndex);
    return mData;
}

void _ByteArrayWriter::skipBy(size_t length) {
    mIndex += length;
}

} // namespace obotcha
