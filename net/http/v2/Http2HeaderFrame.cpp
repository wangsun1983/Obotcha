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

_Http2HeaderFrame::_Http2HeaderFrame(HPackDecoder d,HPackEncoder e):_Http2Frame(),
                                        decoder(d),encoder(e) {
    this->type = Type::Headers;
}

ByteArray _Http2HeaderFrame::toByteArray() {
    ByteArray data = ByteArray::New(1024*32);
    ByteArrayWriter writer = ByteArrayWriter::New(data,st(IO)::Endianness::Big);

    if(isPadding() && paddingData != nullptr) {
        writer->write<byte>(paddingData->size());
    }

    if(isPrioroty()) {
        uint32_t dependencyData = dependencyStream;
        if(exclusive) {
            dependencyData |= (1<<31);
        }
        writer->write<uint32_t>(dependencyData);
        writer->write<byte>(weight);
    }

    encoder->encodeHeaders(streamid,writer,headers);

    if(isPadding()) {
        writer->write(paddingData);
    }

    data->quickShrink(writer->getIndex());
    return data;
}

void _Http2HeaderFrame::load(ByteArray data) {
    ByteArrayReader reader = ByteArrayReader::New(data,st(IO)::Endianness::Big);
    int paddingLength = 0;
    int datasize = this->length;

    if(isPadding()) {
        paddingLength = reader->read<byte>();
        datasize = datasize - paddingLength - 1;
    }

    if(isPrioroty()) {
        uint32_t dependencyData = reader->read<uint32_t>();
        exclusive = (((dependencyData >>24) & 0x80) != 0);
        dependencyStream = dependencyData & 0x7FFFFFFF;
        weight = reader->read<byte>();
        datasize = datasize - 1 - 4;
    }

    ByteArray headerBlock = ByteArray::New(datasize);
    reader->read(headerBlock);

    if(this->isEndHeaders()) {
        HttpHeader h = HttpHeader::New(st(Net)::Protocol::Http_H2);

        decoder->decode(this->streamid,headerBlock,h,true);
        if(headers == nullptr) {
            headers = h;
        } else {
            headers->append(h);
        }
    } else {
        mBuffer = headerBlock;
    }

    if(paddingLength > 0) {
        paddingData = ByteArray::New(paddingLength);
        reader->read(paddingData);
    }
}

ByteArray _Http2HeaderFrame::getSavedData() {
    return mBuffer;
}

HttpHeader _Http2HeaderFrame::getHeader() {
    return headers;
}

void _Http2HeaderFrame::setHeader(HttpHeader h) {
    headers = h;
}

uint32_t _Http2HeaderFrame::getDependency() const {
    return dependencyStream;
}

void _Http2HeaderFrame::setDependency(uint32_t s) {
    dependencyStream = s;
}

ByteArray _Http2HeaderFrame::getPaddingData() {
    this->flags |= Flag::Padded;
    return paddingData;
}

void _Http2HeaderFrame::setPaddingData(ByteArray s) {
    paddingData = s;
}



}
