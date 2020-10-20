#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

const int _ByteArrayWriter::DefaultDataSize = 1024;
const int _ByteArrayWriter::Dynamic = 1;
const int _ByteArrayWriter::Static = 2;

_ByteArrayWriter::_ByteArrayWriter() {
    mData = createByteArray(DefaultDataSize);
    mDataP = mData->toValue();
    mSize = DefaultDataSize;
    mIndex = 0;
    mType = Dynamic;
}

_ByteArrayWriter::_ByteArrayWriter(ByteArray data) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mType = Static;
}

int _ByteArrayWriter::writeShort(int s) {
    if(mIndex > (mSize - sizeof(short))) {
        if(mType == Dynamic) {
            mSize = mData->size()*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    mDataP[mIndex++] = (byte) ((s >> 8) & 0xff);

    if(mIndex == mSize - 1) {
        return -WritePart;
    }

    mDataP[mIndex++] = (byte)  (s& 0xff);

    return WriteSuccess;
}

int _ByteArrayWriter::writeByte(byte v) {
    if(mIndex > (mSize - 1)) {
        if(mType == Dynamic) {
            mSize = mData->size()*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    mDataP[mIndex++] = v;
    return WriteSuccess;
}

int _ByteArrayWriter::writeInt(int v) {
    if(mIndex > (mSize - sizeof(int))) {
        if(mType == Dynamic) {
            mSize = mData->size()*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    mDataP[mIndex++] = (byte) ((v >> 24) & 0xff);
    if(mIndex == mSize - 1) {
        return -WritePart;
    }

    mDataP[mIndex++] = (byte) ((v >> 16) & 0xff);
    if(mIndex == mSize - 1) {
        return -WritePart;
    }

    mDataP[mIndex++] = (byte) ((v >>  8) & 0xff);
    if(mIndex == mSize - 1) {
        return -WritePart;
    }

    mDataP[mIndex++] = (byte)  (v         & 0xff);
    return WriteSuccess;
}

long _ByteArrayWriter::writeLong(long v) {
    if(mIndex > (mSize - sizeof(long))) {
        if(mType == Dynamic) {
            mSize = mData->size()*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    int bytesize = sizeof(long);
    switch(bytesize) {
        case 4: {
            return writeInt(v);
        }

        case 8: {
            mDataP[mIndex++] = (byte) ((v >> 56L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >> 48L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >> 40L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >> 32L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >> 24L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >> 16L) & 0xff);
            mDataP[mIndex++] = (byte) ((v >>  8L) & 0xff);
            mDataP[mIndex++] = (byte)  (v          & 0xff);
            return WriteSuccess;
        }
    }

    return -WriteFail;
}

int _ByteArrayWriter::writeByteArray(ByteArray b) {
    if(mIndex > (mSize - b->size())) {
        if(mType == Dynamic) {
            mSize = (mData->size() + b->size())*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    memcpy(&mDataP[mIndex],b->toValue(),b->size());
    mIndex += b->size();
    return WriteSuccess;
}

int _ByteArrayWriter::writeString(String str) {
    if(mIndex > (mSize - str->size())) {
        if(mType == Dynamic) {
            mSize = (mData->size() + str->size())*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    memcpy(&mDataP[mIndex],str->toChars(),str->size());
    mIndex += str->size();
    return WriteSuccess;
}

int _ByteArrayWriter::writeByteArray(ByteArray b,int length) {
    if(mIndex > (mSize - length)) {
        if(mType == Dynamic) {
            mSize = (mData->size() + length)*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    memcpy(&mDataP[mIndex],b->toValue(),length);
    mIndex += length;
    return WriteSuccess;
}

int _ByteArrayWriter::write(byte *data,int length) {
    if(mIndex > (mSize - length)) {
        if(mType == Dynamic) {
            mSize = (mData->size() + length)*7/4;
            mData->growTo(mSize);
        } else {
            return -WriteFail;
        }
    }

    memcpy(&mDataP[mIndex],data,length);
    mIndex += length;
    return WriteSuccess;
    
}

int _ByteArrayWriter::getIndex() {
    return mIndex;
}

ByteArray _ByteArrayWriter::getByteArray() {
    mData->quickShrink(mSize);
    return mData;
}

}
