#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_ByteArrayWriter::_ByteArrayWriter(ByteArray data) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
}

int _ByteArrayWriter::writeShort(int s) {
    if(mIndex == mSize - 1) {
        return -ByteArrayWriteFail;
    }

    mDataP[mIndex++] = (byte) ((s >> 8) & 0xff);

    if(mIndex == mSize - 1) {
        return -ByteArrayWritePart;
    }

    mDataP[mIndex++] = (byte)  (s        & 0xff);

    return ByteArrayWriteSuccess;
}

int _ByteArrayWriter::writeByte(char v) {
    if(mIndex == mSize - 1) {
        return -ByteArrayWriteFail;
    }

    mDataP[mIndex++] = v;
    return ByteArrayWriteSuccess;
}

int _ByteArrayWriter::writeInt(int v) {
    if(mIndex == mSize - 1) {
        return -ByteArrayWriteFail;
    }

    mDataP[mIndex++] = (byte) ((v >> 24) & 0xff);
    if(mIndex == mSize - 1) {
        return -ByteArrayWritePart;
    }

    mDataP[mIndex++] = (byte) ((v >> 16) & 0xff);
    if(mIndex == mSize - 1) {
        return -ByteArrayWritePart;
    }

    mDataP[mIndex++] = (byte) ((v >>  8) & 0xff);
    if(mIndex == mSize - 1) {
        return -ByteArrayWritePart;
    }

    mDataP[mIndex++] = (byte)  (v         & 0xff);
    return ByteArrayWriteSuccess;
}

long _ByteArrayWriter::writeLong(long v) {
    int bytesize = sizeof(long);
    switch(bytesize) {
        case 4: {
            return writeInt(v);
        }

        case 8: {
            mDataP[mIndex++] = (byte) ((v >> 56L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >> 48L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >> 40L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >> 32L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >> 24L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >> 16L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte) ((v >>  8L) & 0xff);
            if(mIndex == mSize - 1) {
                return -ByteArrayWritePart;
            }
            mDataP[mIndex++] = (byte)  (v          & 0xff);
            return ByteArrayWriteSuccess;
        }
    }

    return ByteArrayWriteSuccess;
}

int _ByteArrayWriter::writeByteArray(ByteArray b) {
    if(mIndex + b->size() < mSize) {
        memcpy(&mDataP[mIndex],b->toValue(),b->size());
        mIndex += b->size();
        return ByteArrayWriteSuccess;
    } else {
        memcpy(&mDataP[mIndex],b->toValue(),mSize - mIndex);
        mIndex = mSize - 1;
        return -ByteArrayWritePart;
    }

    return -ByteArrayWriteFail;
}

int _ByteArrayWriter::getIndex() {
    return mIndex;
}

}
