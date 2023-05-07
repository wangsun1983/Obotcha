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

const int _ByteArrayWriter::DefaultDataSize = 1024;

_ByteArrayWriter::_ByteArrayWriter(int mod):_ByteArrayWriter(createByteArray(DefaultDataSize),mod) {
    mType = Dynamic;
}

_ByteArrayWriter::_ByteArrayWriter(ByteArray data, int mod) {
    mData = data;
    mDataPtr = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mMode = mod;
    mType = Static;
}

void _ByteArrayWriter::reset() {
    mIndex = 0;
}

bool _ByteArrayWriter::preCheck(int size) {
    int needSize = mIndex + size;
    if (mType == Dynamic && needSize > mSize) {
        mSize = (mData->size() + size)* 7 / 4;
        mData->growTo(mSize);
        mDataPtr = mData->toValue();
    }
    return mType == Dynamic || needSize <= mSize;
}

int _ByteArrayWriter::write(ByteArray data, int start,int length) {
    Inspect(!preCheck(length) || start + length > data->size(),-1);
    memcpy(&mDataPtr[mIndex], data->toValue() + start, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(byte *data, int length) {
    Inspect(!preCheck(length),-1);
    memcpy(&mDataPtr[mIndex], data, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(const char *str,int size) {
    int writeSize = (size == -1)?strlen(str):size;
    return write((byte *)str,writeSize);
}


int _ByteArrayWriter::getIndex() {
    return mIndex;
}

void _ByteArrayWriter::setIndex(int index) {
    mIndex = index;
}

int _ByteArrayWriter::getReminderSize() {
    return mData->size() - mIndex;
}

ByteArray _ByteArrayWriter::getByteArray() {
    mData->quickShrink(mIndex);
    return mData;
}

void _ByteArrayWriter::skipBy(int length) {
    mIndex += length;
}

} // namespace obotcha
