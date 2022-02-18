#include "Http2PushPromiseFrame.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

_Http2PushPromiseFrame::_Http2PushPromiseFrame(HPackDecoder d,HPackEncoder e):_Http2Frame() {
    this->type = TypePushPromise;
    this->decoder = d;
    this->encoder = e;
    headers = createHttpHeader(st(NetProtocol)::Http_H2);
    promiseStreamId = 0;
}

ByteArray _Http2PushPromiseFrame::toByteArray() {
    ByteArray data = createByteArray(4*1024); //TODO
    ByteArrayWriter writer = createByteArrayWriter(data,BigEndian);

    if(isPadding() && paddingData != nullptr) {
        writer->writeByte(paddingData->size());
    }

    writer->writeUint32(promiseStreamId);
    encoder->encodeHeaders(streamid,writer,headers);

    if(isPadding() && paddingData != nullptr) {
        writer->writeByteArray(paddingData);
    }

    return data;
}

void _Http2PushPromiseFrame::import(ByteArray data) {
    int size = this->length;
    int paddingLength = 0;
    ByteArrayReader reader = createByteArrayReader(data);
    if(isPadding()) {
        paddingLength = reader->readByte();
        size -= paddingLength;
    }

    uint32_t promiseId = reader->readUint32();
    promiseStreamId = promiseId & 0x7FFFFFFF;
    //decode(int streamId, ByteArray in, HttpHeader headers, bool validateHeaders)
    ByteArray input = createByteArray(size);
    reader->readByteArray(input);
    decoder->decode(streamid,input,headers,false);

    if(paddingLength != 0) {
        paddingData = createByteArray(paddingLength);
        reader->readByteArray(paddingData);
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

uint32_t _Http2PushPromiseFrame::getPromiseStream() {
    return promiseStreamId;
}

void _Http2PushPromiseFrame::setPromiseStream(uint32_t s) {
    promiseStreamId = s;
}

}
