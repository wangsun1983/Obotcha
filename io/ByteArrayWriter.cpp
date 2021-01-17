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

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

const int _ByteArrayWriter::DefaultDataSize = 1024;

_ByteArrayWriter::_ByteArrayWriter(int mod) {
    mData = createByteArray(DefaultDataSize);
    mDataP = mData->toValue();
    mSize = DefaultDataSize;
    mIndex = 0;
    mode = mod;
    mType = Dynamic;
}

_ByteArrayWriter::_ByteArrayWriter(ByteArray data,int mod) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mode = mod;
    mType = Static;
}

bool _ByteArrayWriter::writeSizeCheck(int size) {
    if(mIndex > (mSize - sizeof(short))) {
        if(mType == Dynamic) {
            mSize = mData->size()*7/4;
            mData->growTo(mSize);
        } else {
            return false;
        }
    }

    return true;
}

int _ByteArrayWriter::writeShort(int s) {
    if(!writeSizeCheck(sizeof(short int))) {
        return -1;
    }

    _write(s);
    return 0;
}

int _ByteArrayWriter::writeByte(byte v) {
    if(!writeSizeCheck(sizeof(byte))) {
        return -1;
    }

    mDataP[mIndex++] = v;
    return 0;
}

int _ByteArrayWriter::writeInt(int v) {
    if(!writeSizeCheck(sizeof(int))) {
        return -1;
    }

    _write(v);
    return 0;
}

long _ByteArrayWriter::writeLong(long v) {
    if(!writeSizeCheck(sizeof(int))) {
        return -1;
    }

    _write(v);
    return 0;
}

int _ByteArrayWriter::writeByteArray(ByteArray b) {
    if(!writeSizeCheck(b->size())) {
        return -1;
    }

    memcpy(&mDataP[mIndex],b->toValue(),b->size());
    mIndex += b->size();

    return 0;
}

int _ByteArrayWriter::writeString(String str) {
    if(!writeSizeCheck(str->size())) {
        return -1;
    }

    memcpy(&mDataP[mIndex],str->toChars(),str->size());
    mIndex += str->size();
    return 0;
}

int _ByteArrayWriter::writeString(const char *str) {
    int size = strlen(str);
    if(!writeSizeCheck(size)) {
        return -1;
    }

    memcpy(&mDataP[mIndex],str,size);
    mIndex += size;
    return 0;
}

int _ByteArrayWriter::writeByteArray(ByteArray b,int length) {
    if(!writeSizeCheck(length)) {
        return -1;
    }

    memcpy(&mDataP[mIndex],b->toValue(),length);
    mIndex += length;
    return 0;
}

int _ByteArrayWriter::write(byte *data,int length) {
    if(!writeSizeCheck(length)) {
        return -1;
    }

    memcpy(&mDataP[mIndex],data,length);
    mIndex += length;
    return 0;
    
}

int _ByteArrayWriter::getIndex() {
    return mIndex;
}

ByteArray _ByteArrayWriter::getByteArray() {
    mData->quickShrink(mIndex);
    return mData;
}

void _ByteArrayWriter::updateSize() {
    mSize = mData->size();
}

void _ByteArrayWriter::skipBy(int length) {
    mIndex += length;
}

}
