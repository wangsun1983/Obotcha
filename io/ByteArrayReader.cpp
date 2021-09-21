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

String _ByteArrayReader::readLine() {
    int start = mIndex;
    if (mIndex >= mData->size()) {
        return nullptr;
    }

    while (mIndex < mData->size()) {
        switch (mData->at(mIndex)) {
        case '\r': {
            String result =
                createString((char *)mData->toValue(), start, mIndex - start);
            mIndex++;
            if (mIndex < mData->size() && mData->at(mIndex) == '\n') {
                mIndex++;
            }
            return result;
        }

        case '\n': {
            String result =
                createString((char *)mData->toValue(), start, mIndex - start);
            mIndex++;
            return result;
        } break;

        default:
            mIndex++;
        }
    }

    return nullptr;
}

} // namespace obotcha
