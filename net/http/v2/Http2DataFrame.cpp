#include "Http2DataFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2DataFrame::_Http2DataFrame():_Http2Frame() {
    data = nullptr;
    paddingData = nullptr;
}

ByteArray _Http2DataFrame::toByteArray() {
    int size = data->size();
    if(paddingData != nullptr) {
        this->flags |= FlagPadded;
        size += paddingData->size() + 1/*1 byte padding length*/;
    }

    ByteArray out = createByteArray(size);
    ByteArrayWriter writer = createByteArrayWriter(out,BigEndian);
    if(paddingData != nullptr) {
        writer->writeByte(paddingData->size());
    }

    writer->writeByteArray(data);

    if(paddingData != nullptr) {
        writer->writeByteArray(paddingData);
    }

    return out;
}

void _Http2DataFrame::import(ByteArray s) {
    //check padding flag
    int paddingLength = 0;
    int dataSize = length;

    ByteArrayReader reader = createByteArrayReader(s);

    if((this->flags & FlagPadded) != 0) {
        //it contains padding
        paddingLength = reader->readByte();
        dataSize = dataSize - paddingLength - 1 /*1 byte padding length*/;
    }

    ByteArray data = createByteArray(dataSize);
    reader->readByteArray(data);

    if(paddingLength != 0) {
        paddingData = createByteArray(paddingLength);
        reader->readByteArray(paddingData);
    }
}

ByteArray _Http2DataFrame::getData() {
    return data;
}

void _Http2DataFrame::setData(ByteArray s) {
    data = s;
}

ByteArray _Http2DataFrame::getPaddingData() {
    return paddingData;
}

void _Http2DataFrame::setPaddingData(ByteArray s) {
    paddingData = s;
}



}
