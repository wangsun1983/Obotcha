#include "Http2HeaderFrame.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

/*
+-----------------------------------------------+
|                Length (24)                    |
+---------------+---------------+---------------+
|    0x1 (8)    | 00?0 ??0? (8) |
+-+-------------+---------------+-------------------------------+
|R|                Stream Identifier (31)                       |
+=+=============+===============================================+
|Pad Length? (8)|
+-+-------------+-----------------------------------------------+
|E|                 Stream Dependency? (31)                     |
+-+-------------+-----------------------------------------------+
|  Weight? (8)  |
+-+-------------+-----------------------------------------------+
|                   Header Block Fragment (*)                 ...
+---------------------------------------------------------------+
|                           Padding (*)                       ...
+---------------------------------------------------------------+
 */

_Http2HeaderFrame::_Http2HeaderFrame(HPackDecoder decoder,HPackEncoder encoder):_Http2Frame() {
    this->decoder = decoder;
    this->encoder = encoder;
    dependency = 0;
    exclusive = false;
    this->type = TypeHeaders;
    headers = nullptr;
}

ByteArray _Http2HeaderFrame::toByteArray() {
    ByteArray data = createByteArray(1024*32);
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);

    if(isPadding() && paddingData != nullptr) {
        writer->writeByte(paddingData->size());
    }

    if(isPrioroty()) {
        uint32_t dependencyData = dependency;
        if(exclusive) {
            dependencyData |= (1<<31);
        }
        writer->writeUint32(dependencyData);
        writer->writeByte(weight);
    }

    encoder->encodeHeaders(streamid,writer,headers);

    if(isPadding()) {
        writer->writeByteArray(paddingData);
    }

    data->quickShrink(writer->getIndex());
    return data;
}

void _Http2HeaderFrame::import(ByteArray data) {
    ByteArrayReader reader = createByteArrayReader(data,BigEndian);
    int paddingLength = 0;
    int datasize = this->length;

    if(isPadding()) {
        paddingLength = reader->readByte();
        datasize = datasize - paddingLength - 1;
    }

    if(isPrioroty()) {
        uint32_t dependencyData = reader->readUint32();
        exclusive = (((dependencyData >>24) & 0x80) != 0);
        dependency = dependencyData & 0x7FFFFFFF;
        weight = reader->readByte();
        datasize = datasize - 1 - 4;
    }
    
    ByteArray headerBlock = createByteArray(datasize);
    reader->readByteArray(headerBlock);
    HttpHeader h = createHttpHeader();

    decoder->decode(this->streamid,headerBlock,h,true);
    if(headers == nullptr) {
        headers = h;
    } else {
        headers->addHttpHeader(h);
    }

    if(paddingLength > 0) {
        paddingData = createByteArray(paddingLength);
        reader->readByteArray(paddingData);
    }
}

HttpHeader _Http2HeaderFrame::getHeader() {
    return headers;
}

void _Http2HeaderFrame::setHeader(HttpHeader h) {
    headers = h;
}

ByteArray _Http2HeaderFrame::getPaddingData() {
    this->flags |= FlagPadded;
    return paddingData;
}

void _Http2HeaderFrame::setPaddingData(ByteArray s) {
    paddingData = s;
}



}

