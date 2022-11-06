#include "Object.hpp"
#include "StrongPointer.hpp"

#include "ByteArray.hpp"
#include "ByteArrayReader.hpp"
#include "Inspect.hpp"
#include "String.hpp"

namespace obotcha {

_ByteArrayReader::_ByteArrayReader(ByteArray data, int mod) {
    mData = data;
    mDataP = data->toValue();
    mSize = data->size();
    mIndex = 0;
    mMode = mod;
}

int _ByteArrayReader::read(ByteArray data) {
    // if (mIndex >= mSize) {
    //     return -1;
    // }
    Inspect(mIndex > mSize,-1);

    //int leftSize = mSize - mIndex;
    //int dataSize = data->size();

    int copySize = std::min(mSize - mIndex,data->size());
    //(leftSize < dataSize ? leftSize : dataSize);
    
    memcpy(data->toValue(), &mDataP[mIndex], copySize);
    mIndex += copySize;
    return copySize;
}

int _ByteArrayReader::getIndex() {
    return mIndex;
}

int _ByteArrayReader::getRemainSize() {
    return mSize - mIndex;
}

void _ByteArrayReader::setIndex(int index) {
    mIndex = index;
}

bool _ByteArrayReader::isReadable() {
    return mSize > mIndex;
}

/*
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
*/
} // namespace obotcha
