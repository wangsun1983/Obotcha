#include "Http2DataFrame.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"

namespace obotcha {

_Http2DataFrame::_Http2DataFrame():_Http2Frame() {
    data = nullptr;
    paddingData = nullptr;
    this->type = Type::Data;
}

ByteArray _Http2DataFrame::toByteArray() {
    if(data == nullptr) {
        return nullptr;
    }
    
    int size = data->size();
    if(paddingData != nullptr) {
        this->flags |= Flag::Padded;
        size += paddingData->size() + 1/*1 byte padding length*/;
    }

    ByteArray out = ByteArray::New(size);
    ByteArrayWriter writer = ByteArrayWriter::New(out,st(IO)::Endianness::Big);
    if(paddingData != nullptr) {
        writer->write<byte>(paddingData->size());
    }

    writer->write(data);

    if(paddingData != nullptr) {
        writer->write(paddingData);
    }

    return out;
}

void _Http2DataFrame::load(ByteArray s) {
    //check padding flag
    int paddingLength = 0;
    int dataSize = length;

    ByteArrayReader reader = ByteArrayReader::New(s);

    if((this->flags & Flag::Padded) != 0) {
        //it contains padding
        paddingLength = reader->read<byte>();
        dataSize = dataSize - paddingLength - 1 /*1 byte padding length*/;
    }

    data = ByteArray::New(dataSize);
    reader->read(data);

    if(paddingLength != 0) {
        paddingData = ByteArray::New(paddingLength);
        reader->read(paddingData);
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
