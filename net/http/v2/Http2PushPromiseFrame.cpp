#include "Http2PushPromiseFrame.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

_Http2PushPromiseFrame::_Http2PushPromiseFrame(HPackDecoder d,HPackEncoder e):_Http2Frame(),
                            encoder(e),decoder(d) {
    headers = HttpHeader::New(st(Net)::Protocol::Http_H2);
    this->type = Type::PushPromise;
}

ByteArray _Http2PushPromiseFrame::toByteArray() {
    ByteArray data = ByteArray::New(32*1024);
    ByteArrayWriter writer = ByteArrayWriter::New(data,st(IO)::Endianness::Big);

    if(isPadding() && paddingData != nullptr) {
        writer->write<byte>(paddingData->size());
    }

    writer->write<uint32_t>(promiseStreamId);
    encoder->encodeHeaders(streamid,writer,headers);

    if(isPadding() && paddingData != nullptr) {
        writer->write(paddingData);
    }

    return data;
}

void _Http2PushPromiseFrame::load(ByteArray data) {
    int size = this->length;
    int paddingLength = 0;
    ByteArrayReader reader = ByteArrayReader::New(data);
    if(isPadding()) {
        paddingLength = reader->read<byte>();
        size -= paddingLength;
    }

    uint32_t promiseId = reader->read<uint32_t>();
    promiseStreamId = promiseId & 0x7FFFFFFF;
    //decode(int streamId, ByteArray in, HttpHeader headers, bool validateHeaders)
    ByteArray input = ByteArray::New(size);
    reader->read(input);
    decoder->decode(streamid,input,headers,false);

    if(paddingLength != 0) {
        paddingData = ByteArray::New(paddingLength);
        reader->read(paddingData);
    }
}

void _Http2PushPromiseFrame::setHttpHeaders(HttpHeader h) {
    headers = h;
}

HttpHeader _Http2PushPromiseFrame::getHttpHeaders() {
    return headers;
}

ByteArray _Http2PushPromiseFrame::getPaddingData() {
    return paddingData;
}

void _Http2PushPromiseFrame::setPaddingData(ByteArray s) {
    paddingData = s;
}

uint32_t _Http2PushPromiseFrame::getPromiseStream() const {
    return promiseStreamId;
}

void _Http2PushPromiseFrame::setPromiseStream(uint32_t s) {
    promiseStreamId = s;
}

}
