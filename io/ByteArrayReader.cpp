#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"
#include "String.hpp"

namespace obotcha {

_ByteArrayReader::_ByteArrayReader(ByteArray data, int mod) {
    this->mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mode = mod;
}

int _ByteArrayReader::readShort() {
    short int value = 0;
    _read(value);
    return value;
}

int _ByteArrayReader::readByte() {
    if (mIndex >= mSize) {
        return -1;
    }

    int value = mDataP[mIndex];
    mIndex++;

    return value;
}

int _ByteArrayReader::readInt() {
    int value = 0;
    _read(value);
    return value;
}

long _ByteArrayReader::readLong() {
    long value = 0;
    _read(value);
    return value;
}

uint32_t _ByteArrayReader::readUint32() {
    uint32_t value = 0;
    _read(value);
    return value;
}

uint16_t _ByteArrayReader::readUint16() {
    uint16_t value = 0;
    _read(value);
    return value;
}

int _ByteArrayReader::readByteArray(ByteArray d) {
    if (mIndex >= mSize) {
        return -1;
    }

    int leftSize = mSize - mIndex;
    int dataSize = d->size();

    int copySize = (leftSize < dataSize ? leftSize : dataSize);
    memcpy(d->toValue(), &mDataP[mIndex], copySize);
    mIndex += copySize;
    return copySize;
}

int _ByteArrayReader::getIndex() { return mIndex; }

int _ByteArrayReader::getRemainSize() { return mSize - mIndex; }

void _ByteArrayReader::setIndex(int index) { mIndex = index; }

#if 0
int _ByteArrayReader::appendWithAdjustment(ByteArray d) {
    int size = mData->size() - mIndex + d->size();
    ByteArray data = createByteArray(size);
    if (mIndex < mData->size()) {
        memcpy(data->toValue(), mData->toValue() + mIndex,
               mData->size() - mIndex);
    }

    memcpy((data->toValue() + (mData->size() - mIndex)), d->toValue(),
           d->size());
    mData = data;
    mDataP = mData->toValue();
    mSize = data->size();
    mIndex = 0;
    return 0;
}
#endif

String _ByteArrayReader::readLine() {
    int start = mIndex;
    if (mIndex >= mData->size()) {
        return nullptr;
    }

    while (start < mData->size()) {
        switch (mData->at(start)) {
            case '\r':{
                String result =
                    createByteArray((const byte *)mData->toValue() + mIndex, start - mIndex)->toString();
                start++;
                if (start < mData->size() && mData->at(start) == '\n') {
                    start++;
                }
                mIndex = start;
                return result;
            }

            case '\n': {
                String result =
                    createByteArray((const byte *)mData->toValue() + mIndex, start - mIndex)->toString();
                
                start++;
                if (start < mData->size() && mData->at(start) == '\r') {
                    start++;
                }
                mIndex = start;
                return result;
            } 
            break;

            default:
                start++;
        }
    }

    //last
    if(mIndex != mData->size()) {
        String result =
                createByteArray((const byte *)mData->toValue() + mIndex, mData->size() - mIndex)->toString();
        mIndex = mData->size();
        return result;
    }

    return nullptr;
}

} // namespace obotcha
