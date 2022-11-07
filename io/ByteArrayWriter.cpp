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

namespace obotcha {

const int _ByteArrayWriter::DefaultDataSize = 1024;

_ByteArrayWriter::_ByteArrayWriter(int mod) {
    mData = createByteArray(DefaultDataSize);
    mDataP = mData->toValue();
    mSize = DefaultDataSize;
    mIndex = 0;
    mMode = mod;
    mType = Dynamic;
}

_ByteArrayWriter::_ByteArrayWriter(ByteArray data, int mod) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mMode = mod;
    mType = Static;
}

void _ByteArrayWriter::reset() {
    mIndex = 0;
}

bool _ByteArrayWriter::preCheck(int size) {
    if ((mIndex + size) > mSize) {
        if (mType == Dynamic) {
            mSize = mData->size() * 7 / 4;
            mData->growTo(mSize);
            mDataP = mData->toValue();
            return true;
        } 

        return false;
    }
    return true;
}

int _ByteArrayWriter::write(ByteArray data, int start,int length) {
    if (!preCheck(length) || start + length > data->size()) {
        return -1;
    }

    memcpy(&mDataP[mIndex], data->toValue() + start, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(byte *data, int length) {
    if (!preCheck(length)) {
        return -1;
    }

    memcpy(&mDataP[mIndex], data, length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(const char *str,int size) {
    if(size == -1) {
        size = strlen(str);
    }
    return write((byte *)str,size);
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
