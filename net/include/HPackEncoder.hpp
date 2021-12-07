#ifndef __OBOTCHA_HPACK_ENCODER_HPP__
#define __OBOTCHA_HPACK_ENCODER_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ByteArrayWriter.hpp"
#include "HPackHuffmanEncoder.hpp"
#include "HPackDynamicTable.hpp"
#include "HPackStaticTable.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_CLASS(HPackEncoderEntry) IMPLEMENTS(HPackTableItem) {
public:
    // These fields comprise the doubly linked list used for iteration.
    sp<_HPackEncoderEntry> before;
    sp<_HPackEncoderEntry> after;

    // These fields comprise the chained list for header fields with the same hash.
    sp<_HPackEncoderEntry> next;
    int hash;

    // This is used to compute the index in the dynamic table.
    int index;

    /**
     * Creates new entry.
     */
    _HPackEncoderEntry(int hash, String name, String value, int index, sp<_HPackEncoderEntry> next);

    /**
     * Removes this entry from the linked list.
     */
    void remove();

    /**
     * Inserts this entry before the specified existing entry in the list.
     */
    void addBefore(sp<_HPackEncoderEntry> existingEntry);
};


DECLARE_CLASS(HPackEncoder) {

public:
    _HPackEncoder();

private:
    static const int HuffCodeThreshold;

    void encodeHeader(String name,String value,bool isSensitive,long headerSize);

    void encodeInteger(int mask,int n,long i);
    void encodeString(String data);
    void encodeLiteral(String name,String value,int indexType,int nameIndex);

    int getNameIndex(String name);

    ByteArrayWriter writer;
    HPackHuffmanEncoder mHuffEncoder;
    HPackStaticTable mStaticTable;

    /*
    To decompress header blocks, a decoder only needs to maintain a
    dynamic table (see Section 2.3.2) as a decoding context.  No other
    dynamic state is needed.

    When used for bidirectional communication, such as in HTTP, the
    encoding and decoding dynamic tables maintained by an endpoint are
    completely independent, i.e., the request and response dynamic tables
    are separate.
     */
    HPackEncoderEntry mEncoderTableHeader;
};

}

#endif
