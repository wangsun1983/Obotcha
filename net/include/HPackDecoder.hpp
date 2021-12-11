#ifndef __OBOTCHA_HPACK_DECODER_HPP__
#define __OBOTCHA_HPACK_DECODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArrayWriter.hpp"
#include "HPackHuffmanEncoder.hpp"
#include "HPackDynamicTable.hpp"
#include "HPackStaticTable.hpp"
#include "String.hpp"
#include "HttpHeader.hpp"
#include "HPack.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {

DECLARE_CLASS(HPackDecoderSink) {
public:
    void appendToHeaderList(String name, String value);
    void finish();
};

DECLARE_CLASS(Http2HeadersSink) IMPLEMENTS(HPackDecoderSink) {

public:
    _Http2HeadersSink(int streamId, HttpHeader headers, long maxHeaderListSize, bool validate);
    void finish();
    void appendToHeaderList(String name, String value);

private:
    HttpHeader headers;
    long maxHeaderListSize;
    int streamId;
    bool validate;
    long headersLength;
    bool exceededMaxLength;
    int previousType;
    bool isError;
};

DECLARE_CLASS(HPackDecoder) {
public:
    _HPackDecoder(long maxHeaderListSize = st(HPack)::MaxHeaderListSize, 
                  int maxHeaderTableSize = st(HPack)::DefaultHeaderTableSize);

    /*
      rfc7540 
      8.1.2.1.  Pseudo-Header Fields
      While HTTP/1.x used the message start-line (see [RFC7230],
      Section 3.1) to convey the target URI, the method of the request, and
      the status code for the response, HTTP/2 uses special pseudo-header
      fields beginning with ':' character (ASCII 0x3a) for this purpose.
   */
    enum HeaderType {
        RegularHeader = 0,
        RequestPseudoHeader,
        ResponsePsedoHeader
    };

    static int validate(int streamId, String name,int previousHeaderType);

private:
    enum DecodeStatus {
        ReadHeaderRepresentation = 0,
        ReadMaxDynamicTableSize,
        ReadIndexedHeader,
        ReadIndexedHeaderName,
        ReadLiteralHeaderNameLengthPrefix,
        ReadLiteralHeaderNameLength,
        ReadLiteralHeaderName,
        ReadLiteralHeaderValueLengthPrefix,
        ReadLiteralHeaderValueLength,
        ReadLiteraHeaderValue,
    };

    int decode(int streamId, ByteArray in, HttpHeader headers, bool validateHeaders);
    int decode(ByteArray in,Http2HeadersSink sink);

    HPackTableItem getIndexedHeader(int index);

    long decodeULE128(ByteArrayReader in, long result);
    void setDynamicTableSize(long dynamicTableSize);

    HPackDynamicTable mDynamicTable;
    long maxHeaderListSize;
    long maxDynamicTableSize;
    long encoderMaxDynamicTableSize;
    int maxHeaderTableSize;
    HPackStaticTable mStaticTable;

    bool maxDynamicTableSizeChangeRequired;
};

}

#endif
