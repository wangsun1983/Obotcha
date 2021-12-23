#include "HPackDecoder.hpp"
#include "HttpPacket.hpp"
#include "Log.hpp"
#include "ByteArrayReader.hpp"

namespace obotcha {


//-------------------Http2HeadersSink---------------------
_Http2HeadersSink::_Http2HeadersSink(int streamId, HttpHeader headers, long maxHeaderListSize, bool validate) {
    this->headers = headers;
    this->maxHeaderListSize = maxHeaderListSize;
    this->streamId = streamId;
    this->validate = validate;
    this->isError = false;
}

void _Http2HeadersSink::finish() {
    if(isError) {
        LOG(ERROR)<<"Http2HeadersSink decode error,streamId is "<<streamId;
    }
}

void _Http2HeadersSink::appendToHeaderList(String name, String value) {
    //headersLength += HpackHeaderField.sizeOf(name, value);
    headersLength += st(HPackTableItem)::sizeOf(name,value);
    exceededMaxLength |= headersLength > maxHeaderListSize;

    if (exceededMaxLength || isError) {
        // We don't store the header since we've already failed validation requirements.
        return;
    }

    if (validate) {
        previousType = st(HPackDecoder)::validate(streamId, name, previousType);
        if(previousType == -1) {
            return;
        }
    }

    headers->set(name, value);
}



//-------------------HPackDecoder---------------------
_HPackDecoder::_HPackDecoder(long maxHeaderListSize, int maxHeaderTableSize) {
    this->maxHeaderListSize = maxHeaderListSize;
    this->maxHeaderTableSize = maxHeaderTableSize;
    this->maxDynamicTableSize = maxHeaderTableSize;
    this->encoderMaxDynamicTableSize = maxHeaderTableSize;
    mDynamicTable = createHPackDynamicTable(maxHeaderTableSize);
    mStaticTable = createHPackStaticTable();
    mHuffmanDecoder = createHPackHuffmanDecoder();
}

//check request head or response head
int _HPackDecoder::validate(int streamId, String name,int previousHeaderType) {
    int headid = st(HttpHeader)::findId(name);
    
    switch(headid) {
        case st(HttpHeader)::TypeStatus:
        case st(HttpHeader)::TypeMethod:
        case st(HttpHeader)::TypePath:
        case st(HttpHeader)::TypeScheme:
        case st(HttpHeader)::TypeProtocol:
        case st(HttpHeader)::TypeAuthority: {
            if (previousHeaderType == RegularHeader) {
                LOG(ERROR)<<"Pseudo-header field '"<<name->getStdString()<<"' found after regular header.";
                return -1;
            }

            if(headid == st(HttpHeader)::TypeStatus) {
                return ResponsePsedoHeader;
            }

            return RequestPseudoHeader;
        }
        break;
    }

    return RegularHeader;
}

int _HPackDecoder::decode(int streamId, ByteArray in, HttpHeader headers, bool validateHeaders) {
    Http2HeadersSink sink = createHttp2HeadersSink(streamId, headers, maxHeaderListSize, validateHeaders);
    int ret = decode(in, sink);

    // Now that we've read all of our headers we can perform the validation steps. We must
    // delay throwing until this point to prevent dynamic table corruption.
    sink->finish();
    return ret;
}

int _HPackDecoder::decode(ByteArray in,Http2HeadersSink sink) {
    int index = 0;
    int nameLength = 0;
    int valueLength = 0;
    byte state = ReadHeaderRepresentation;
    bool huffmanEncoded = false;
    String name = nullptr;
    int indexType = st(HPack)::None;

    ByteArrayReader reader = createByteArrayReader(in,BigEndian);
    byte v = 0;
    while(reader->isReadable()) {
        printf("decode start is %d \n",state);
        switch(state) {
            //rfc7541#section-6.1
            case ReadHeaderRepresentation: {
                byte b = reader->readByte();
                printf("ReadHeaderRepresentation,b is %x \n",b);
                //Dynamic Table Size Update
                /*
                    rfc7541
                    6.3.  Dynamic Table Size Update
                    A dynamic table size update signals a change to the size of the
                    dynamic table.

                    　0   1   2   3   4   5   6   7
                    +---+---+---+---+---+---+---+---+
                    | 0 | 0 | 1 |   Max size (5+)   |
                    +---+---------------------------+
                */
                if (maxDynamicTableSizeChangeRequired && (b & 0xE0) != 0x20) {
                    LOG(ERROR)<<"HpackEncoder MUST signal maximum dynamic table size change";
                    return -1;
                }

                if ((b&0x80) == 0x80) {
                    printf("Indexed Header Field,b is %x \n",b);
                    /*
                        rfc7541
                        6.1.  Indexed Header Field Representation
                        An indexed header field representation identifies an entry in either
                        the static table or the dynamic table (see Section 2.3).

                          0   1   2   3   4   5   6   7
                        +---+---+---+---+---+---+---+---+
                        | 1 |        Index (7+)         |
                        +---+---------------------------+
                    */
                    // Indexed Header Field
                    index = b & 0x7F;
                    printf("Indexed Header Field,index is %x \n",index);
                    switch (index) {
                        case 0:
                            /*
                            The index value of 0 is not used.  It MUST be treated as a decoding
                            error if found in an indexed header field representation.
                            */
                            LOG(ERROR)<<"HpackEncoder signal illegal index ";
                            return -1;
                        case 0x7F:
                            /*
                                if index > 2^N - 1,set  Index's bit to 111...
                                5.1.  Integer Representation
                                  0   1   2   3   4   5   6   7
                                +---+---+---+---+---+---+---+---+
                                | ? | ? | ? | 1   1   1   1   1 |
                                +---+---+---+-------------------+
                                | 1 |    Value-(2^N-1) LSB      |
                                +---+---------------------------+
                                                ...
                                +---+---------------------------+
                                | 0 |    Value-(2^N-1) MSB      |
                                +---+---------------------------+
                            */
                            state = ReadIndexedHeader;
                            break;
                        default:
                            HPackTableItem indexedHeader = getIndexedHeader(index);
                            sink->appendToHeaderList(indexedHeader->name, indexedHeader->value);
                    }
                } else if ((b & 0x40) == 0x40) {
                    printf("Literal Header Field with Incremental Indexing,b is %x \n",b);
                    /*
                        rfc7541
                        6.2.1.  Literal Header Field with Incremental Indexing
                        A literal header field with incremental indexing representation
                        results in appending a header field to the decoded header list and
                        inserting it as a new entry into the dynamic table.

                        Figure 1:Literal Header Field with Incremental Indexing -- Indexed Name
                          0   1   2   3   4   5   6   7
                        +---+---+---+---+---+---+---+---+
                        | 0 | 1 |      Index (6+)       |
                        +---+---+-----------------------+
                        | H |     Value Length (7+)     |
                        +---+---------------------------+
                        | Value String (Length octets)  |
                        +-------------------------------+

                        Figure 2: Literal Header Field with Incremental Indexing -- New Name
                          0   1   2   3   4   5   6   7
                        +---+---+---+---+---+---+---+---+
                        | 0 | 1 |           0           |
                        +---+---+-----------------------+
                        | H |     Name Length (7+)      |
                        +---+---------------------------+
                        |  Name String (Length octets)  |
                        +---+---------------------------+
                        | H |     Value Length (7+)     |
                        +---+---------------------------+
                        | Value String (Length octets)  |
                        +-------------------------------+
                    */
                    // Literal Header Field with Incremental Indexing
                    indexType = st(HPack)::Incremental;
                    index = (b & 0x3F);
                    printf("Literal Header Field with Incremental Indexing,index is %x \n",index);

                    switch (index) {
                        case 0:
                            //(Figure 2)
                            state = ReadLiteralHeaderNameLengthPrefix;
                            break;
                        case 0x3F:
                            state = ReadIndexedHeader;
                            break;
                        default:
                            // Index was stored as the prefix
                            //(Figure 1)
                            HPackTableItem indexedHeader = getIndexedHeader(index);
                            name = indexedHeader->name;
                            printf("Index was stored as the prefix,name is %s \n",name->toChars());
                            nameLength = name->size();
                            printf("Index was stored as the prefix,nameLength is %d \n",nameLength);
                            state = ReadLiteralHeaderValueLengthPrefix;;
                    }
                } else if ((b & 0x20) == 0x20) {
                    printf("Dynamic Table Size Update Indexing,b is %x \n",b);
                    // Dynamic Table Size Update
                    /*
                        A dynamic table size update signals a change to the size of the
                        dynamic table.
                          0   1   2   3   4   5   6   7
                        +---+---+---+---+---+---+---+---+
                        | 0 | 0 | 1 |   Max size (5+)   |
                        +---+---------------------------+
                        A dynamic table size update starts with the '001' 3-bit pattern,
                        followed by the new maximum size, represented as an integer with a
                        5-bit prefix
                     */
                    index = (b & 0x1F);
                    if (index == 0x1F) {
                        //size is too large,can not parse direct
                        state = ReadMaxDynamicTableSize;
                    } else {
                        setDynamicTableSize(index);
                        state = ReadHeaderRepresentation;
                    }
                } else {
                    printf("Literal Header Field without Indexing / never Indexed,b is %x \n",b);
                    // Literal Header Field without Indexing / never Indexed
                    indexType = (b & 0x10) == 0x10 ? st(HPack)::Never : st(HPack)::None;
                    index = b & 0x0F;
                    printf("Literal Header Field without Indexing / never Indexed,index is %x \n",index);
                    switch (index) {
                        case 0:
                            state = ReadLiteralHeaderNameLengthPrefix;
                            break;
                        case 0x0F:
                            state = ReadIndexedHeaderName;
                            break;
                        default:
                            // Index was stored as the prefix
                            name = getIndexedHeader(index)->name;
                            nameLength = name->size();
                            state = ReadLiteralHeaderValueLengthPrefix;
                    }
                }
                break;
            }

            case ReadMaxDynamicTableSize: {
                setDynamicTableSize(decodeULE128(reader, (long) index));
                state = ReadHeaderRepresentation;
                break;
            }

            case ReadIndexedHeader: {
                HPackTableItem indexedHeader = getIndexedHeader(decodeULE128(reader, index));
                sink->appendToHeaderList(indexedHeader->name, indexedHeader->value);
                state = ReadHeaderRepresentation;
                break;
            }

            case ReadIndexedHeaderName:{
                HPackTableItem item = getIndexedHeader(decodeULE128(in, index));
                name = item->name;
                nameLength = name->size();
                state = ReadLiteralHeaderValueLengthPrefix;
                break;
            }

            case ReadLiteralHeaderNameLengthPrefix: {
                byte b = reader->readByte();
                huffmanEncoded = (b & 0x80) == 0x80;
                index = b & 0x7F;
                if (index == 0x7f) {
                    state = ReadLiteralHeaderNameLength;
                } else {
                    nameLength = index;
                    state = ReadLiteralHeaderName;
                }
                break;
            }

            case ReadLiteralHeaderNameLength: {
                nameLength = decodeULE128(reader, index);
                state = ReadLiteralHeaderName;
                break;
            }

            case ReadLiteralHeaderName: {
                // Wait until entire name is readable
                if (reader->getRemainSize() < nameLength) {
                    LOG(ERROR)<<"HPackDecoder not Enough Header Name Data!!!";
                    return -1;
                    //throw notEnoughDataException(in);
                }

                ByteArray data = createByteArray(nameLength);
                reader->readByteArray(data);
                if(huffmanEncoded) {
                    name = mHuffmanDecoder->decode(data)->toString();
                } else {
                    name = data->toString();
                }
                
                state = ReadLiteralHeaderValueLengthPrefix;
                break;
            }

            case ReadLiteralHeaderValueLengthPrefix: {
                byte b = reader->readByte();
                printf("ReadLiteralHeaderValueLengthPrefix b is %x \n",b);
                huffmanEncoded = (b & 0x80) == 0x80;
                index = (b & 0x7F);
                printf("ReadLiteralHeaderValueLengthPrefix,index is %x \n",index);
                switch (index) {
                    case 0x7f:
                        state = ReadLiteralHeaderValueLength;
                        break;
                    case 0:
                        insertHeader(sink, name, "", indexType);
                        state = ReadHeaderRepresentation;
                        break;
                    default:
                        valueLength = index;
                        state = ReadLiteralHeaderValue;
                }
                break;
            }

            case ReadLiteralHeaderValueLength: {
                // Header Value is a Literal String
                valueLength = decodeULE128(in, index);

                state = ReadLiteralHeaderValue;
                break;
            }

            case ReadLiteralHeaderValue: {
                // Wait until entire value is readable
                if (reader->getRemainSize() < valueLength) {
                    LOG(ERROR)<<"HPackDecoder not Enough Header Value Data!!!";
                    return -1;
                }

                ByteArray data = createByteArray(valueLength);
                reader->readByteArray(data);
                String value = nullptr;
                if(huffmanEncoded) {
                    value = mHuffmanDecoder->decode(data)->toString();
                } else {
                    value = data->toString();
                }
                printf("parse name is %s ,value is %s\n",name->toChars(),value->toChars());
                insertHeader(sink, name, value, indexType);
                state = ReadHeaderRepresentation;
            }
            break;
        }
    }
}

HPackTableItem _HPackDecoder::getIndexedHeader(int index) {
    if (index <= mStaticTable->size()) {
        return mStaticTable->get(index);
    }
    if (index - mStaticTable->size() <= mDynamicTable->size()) {
        return mDynamicTable->getEntry(index - mStaticTable->size());
    }
    return nullptr;
}

long _HPackDecoder::decodeULE128(ByteArrayReader in, long result) {
    if(result <= 0x7f && result >= 0) {
        LOG(ERROR)<<"HPackDecoder,decodeULE128 param is invalid,it is "<<result;
        return -1;
    }

    bool resultStartedAtZero = (result == 0);
    int end = in->getRemainSize();
    for (int readerIndex = in->getIndex(), shift = 0; readerIndex < end; ++readerIndex, shift += 7) {
        byte b = in->readByte();
        if (shift == 56 && ((b & 0x80) != 0 || b == 0x7F && !resultStartedAtZero)) {
            // the maximum value that can be represented by a signed 64 bit number is:
            // [0x01L, 0x7fL] + 0x7fL + (0x7fL << 7) + (0x7fL << 14) + (0x7fL << 21) + (0x7fL << 28) + (0x7fL << 35)
            // + (0x7fL << 42) + (0x7fL << 49) + (0x7eL << 56)
            // OR
            // 0x0L + 0x7fL + (0x7fL << 7) + (0x7fL << 14) + (0x7fL << 21) + (0x7fL << 28) + (0x7fL << 35) +
            // (0x7fL << 42) + (0x7fL << 49) + (0x7fL << 56)
            // this means any more shifts will result in overflow so we should break out and throw an error.
            LOG(ERROR)<<"HPackDecoder,decodeULE128 to long exception!!!";
        }

        if ((b & 0x80) == 0) {
            return result + ((b & 0x7FL) << shift);
        }
        result += (b & 0x7FL) << shift;
    }

    return -1;
}

void _HPackDecoder::setDynamicTableSize(long dynamicTableSize) {
    if (dynamicTableSize > maxDynamicTableSize) {
        LOG(ERROR)<<"HPackDecoder dynamicTable size is too large,it is "<<dynamicTableSize;
        return;
    }
    
    encoderMaxDynamicTableSize = dynamicTableSize;
    maxDynamicTableSizeChangeRequired = false;
    mDynamicTable->setCapacity(dynamicTableSize);
}

void _HPackDecoder::insertHeader(Http2HeadersSink sink, String name, String value, int type) {
    sink->appendToHeaderList(name, value);

    switch (type) {
        case st(HPack)::None:
        case st(HPack)::Never:
            break;

        case st(HPack)::Incremental:
            mDynamicTable->add(createHPackTableItem(name,value));
            break;

        default:
            LOG(ERROR)<<"should not reach here";
    }
}

}

