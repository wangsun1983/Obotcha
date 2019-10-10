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

    int ss = mSize - mIndex;
    if(d->size() < ss) {
        memcpy(d->toValue(),&mDataP[mIndex],d->size());
        mIndex += d->size();
        return d->size();
    } else {
        memcpy(d->toValue(),&mDataP[mIndex],ss);
        mIndex += ss;
        return ss;
    }

    return -1;
}

int _ByteArrayReader::getIndex() {
    return mIndex;
}

String _ByteArrayReader::readLine() {
    int start = mIndex;
    if(mIndex >= mData->size()) {
        return nullptr;
    }

    while(mIndex < mData->size()) {
        switch(mData->at(mIndex)) {
            case '\r':{
                String result = createString(mData->toValue(),start,mIndex - start);
                mIndex++;
                if(mIndex < mData->size() && mData->at(mIndex) == '\n') {
                    mIndex++;
                }
                return result;
            }

            case '\n': {
                String result = createString(mData->toValue(),start,mIndex - start);
                mIndex++;
                return result;
            }
            break;

            default:
            mIndex++;
        }
    }

    return nullptr;
}

int _ByteArrayReader::getRemainSize() {
    return mSize - mIndex;
}

int _ByteArrayReader::setIndex(int index) {
    mIndex = index;
}

int _ByteArrayReader::appendWithAdjustment(ByteArray d) {
    //mData->append(d);
    int size = mData->size() - mIndex + d->size();
    ByteArray data = createByteArray(size);
    if(mIndex < mData->size()) {
        memcpy(data->toValue(),mData->toValue() + mIndex,mData->size() - mIndex);
    }
    
    memcpy((data->toValue() + (mData->size() - mIndex)),d->toValue(),d->size());
    mData = data;
    mDataP = mData->toValue();
    mSize = data->size();
    mIndex = 0;
    return 0;
}

}
