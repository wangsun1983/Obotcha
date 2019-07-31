#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

_ByteArrayReader::_ByteArrayReader(ByteArray data) {
    this->mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mResult = ByteArrayReadSuccess;
    mIndex = 0;
}

int _ByteArrayReader::readShort() {
    if(mIndex >= mSize) {
        mResult = ByteArrayReadFail;
        return 0;
    }

    mResult = ByteArrayReadSuccess;

    if (mSize - mIndex < 2) {
      int s = (readByte() & 0xff) << 8
          |   (readByte() & 0xff);
      return s;
    }
   
    return (mDataP[mIndex++] & 0xff) << 8
        |   (mDataP[mIndex++] & 0xff);
}

int _ByteArrayReader::readByte() {
    if(mIndex >= mSize) {
        mResult = ByteArrayReadFail;
        return 0;
    }
    
    int value = mDataP[mIndex];
    mIndex++;

    return value;
}

int _ByteArrayReader::readInt() {
    if(mIndex >= mSize) {
        mResult = ByteArrayReadFail;
        return 0;
    }

    mResult = ByteArrayReadSuccess;

    if (mSize - mIndex < 4) {
        int value = (readByte() & 0xff) << 24
          |  (readByte() & 0xff) << 16
          |  (readByte() & 0xff) <<  8
          |  (readByte() & 0xff);
        return value;
    }

    return (mDataP[mIndex++] & 0xff) << 24
        |   (mDataP[mIndex++] & 0xff) << 16
        |   (mDataP[mIndex++] & 0xff) <<  8
        |   (mDataP[mIndex++] & 0xff);
}

long _ByteArrayReader::readLong() {
    if(mIndex >= mSize) {
        mResult = ByteArrayReadFail;
        return 0;
    }

    mResult = ByteArrayReadSuccess;

    int bytesize = sizeof(long);
    switch(bytesize) {
        case 4:
        return readInt();

        case 8:
        {
            if(mSize - mIndex < 8) {
                return (readInt() & 0xffffffffL) << 32
                  |  (readInt() & 0xffffffffL);
            }

            long v = (mDataP[mIndex++] & 0xffL) << 56
                |    (mDataP[mIndex++] & 0xffL) << 48
                |    (mDataP[mIndex++] & 0xffL) << 40
                |    (mDataP[mIndex++] & 0xffL) << 32
                |    (mDataP[mIndex++] & 0xffL) << 24
                |    (mDataP[mIndex++] & 0xffL) << 16
                |    (mDataP[mIndex++] & 0xffL) <<  8
                |    (mDataP[mIndex++] & 0xffL);

            return v;
        }
    }

    mResult = ByteArrayReadFail;
    return 0;
}

int _ByteArrayReader::readByteArray(ByteArray d) {
    if(mIndex >= mSize) {
        mResult = ByteArrayReadFail;
        return -1;
    }
    printf("readByteArray \n");
    
    int ss = mSize - mIndex;
    if(d->size() < ss) {
        memcpy(d->toValue(),&mDataP[mIndex],d->size());
        printf("copy trace1 ,length is %d,mIndex is %d \n",d->size(),mIndex);
        mIndex += d->size();
    } else {
        printf("copy trace2,ss is %d,mIndex is %d \n",ss,mIndex);
        memcpy(d->toValue(),&mDataP[mIndex],ss);
        mIndex += ss;
    }

    return 0;
}

int _ByteArrayReader::getIndex() {
    return mIndex;
}


}
