#include "HPackEncoder.hpp"
#include "IllegalArgumentException.hpp"
#include "HPack.hpp"
#include "HPackStaticTable.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "HPackSensitiveTable.hpp"

namespace obotcha {

//------HPackEncoderEntry------
_HPackEncoderEntry::_HPackEncoderEntry(int hash, String name, String value, int index, HPackEncoderEntry next) {
    this->name = name;
    this->value = value;
    this->index = index;
    this->hash = hash;
    this->next = next;
}

/**
 * Removes this entry from the linked list.
 */
void _HPackEncoderEntry::remove() {
    before->after = after;
    after->before = before;
    before = nullptr; // null references to prevent nepotism in generational GC.
    after = nullptr;
    next = nullptr;
}

/**
 * Inserts this entry before the specified existing entry in the list.
 */
void _HPackEncoderEntry::addBefore(HPackEncoderEntry existingEntry) {
    after = existingEntry;
    before = existingEntry->before;
    before->after = AutoClone(this);
    after->before = AutoClone(this);
}

//------HPackEncoder-----
const int _HPackEncoder::HuffCodeThreshold = 512;

_HPackEncoder::_HPackEncoder(bool ignoreMaxHeaderListSize,int tableSize) {
    mHuffEncoder = createHPackHuffmanEncoder();
    mStaticTable = createHPackStaticTable();
    this->ignoreMaxHeaderListSize = ignoreMaxHeaderListSize;
    dynamicHeaderSize = tableSize;
    maxDynamicTableSize = st(HPack)::DefaultHeaderTableSize;
    maxHeaderListSize = st(HPack)::MaxHeaderListSize;
    maxHeaderTableSize = st(HPack)::MaxHeaderTableSize;

    this->mEncoderEntries = createList<HPackEncoderEntry>(tableSize);
    mask = (byte)(tableSize - 1);

    header = createHPackEncoderEntry(-1, "","",st(Integer)::MAX_VALUE, nullptr);
    header->before = header->after = header;
}


void _HPackEncoder::encodeHeaders(int streamId, ByteArrayWriter writer, HttpHeader headers) {
    this->writer = writer;
    if (ignoreMaxHeaderListSize) {
        encodeHeadersIgnoreMaxHeaderListSize(headers);
    } else {
        encodeHeadersEnforceMaxHeaderListSize(streamId,headers);
    }
}

void _HPackEncoder::encodeHeadersEnforceMaxHeaderListSize(int streamId, HttpHeader headers) {
    long headerSize = 0;
    // To ensure we stay consistent with our peer check the size is valid before we potentially modify HPACK state.
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        String name = iterator->getKey();
        String value = iterator->getValue();
        // OK to increment now and check for bounds after because this value is limited to unsigned int and will not
        // overflow.
        headerSize += st(HPackTableItem)::sizeOf(name, value);
        if (headerSize > maxHeaderListSize) {
            Trigger(ArrayIndexOutOfBoundsException,"over size");
        }
    }
    encodeHeadersIgnoreMaxHeaderListSize(headers);
}

void _HPackEncoder::encodeHeadersIgnoreMaxHeaderListSize(HttpHeader headers) {
    auto iterator = headers->getIterator();
    while (iterator->hasValue()) {
        String name = iterator->getKey();
        String value = iterator->getValue();
        encodeHeader(name, value, st(HPackSensitiveTable)::isSensitive(name),
                        st(HPackTableItem)::sizeOf(name, value));
    }
}

void _HPackEncoder::encodeHeader(String name,String value,bool isSensitive,long headerSize) {
    // If the header value is sensitive then it must never be indexed
    if (isSensitive) {
        int nameIndex = getNameIndex(name);
        encodeLiteral(name, value, st(HPack)::Never, nameIndex);
        return;
    }

    // If the peer will only use the static table
    if (maxHeaderTableSize == 0) {
        int staticTableIndex = mStaticTable->getIndexInsensitive(name, value);
        if (staticTableIndex == -1) {
            int nameIndex = mStaticTable->getIndex(name);
            encodeLiteral(name, value, st(HPack)::None, nameIndex);
        } else {
            encodeInteger(0x80, 7, staticTableIndex);
        }
        return;
    }

    // If the headerSize is greater than the max table size then it must be encoded literally
    if (headerSize > maxHeaderTableSize) {
        int nameIndex = getNameIndex(name);
        encodeLiteral(name, value, st(HPack)::None, nameIndex);
        return;
    }

    HPackTableItem headerField = getEntry(name, value);
    if (headerField != nullptr) {
        int index = getIndex(headerField->id) + mStaticTable->size();
        // Section 6.1. Indexed Header Field Representation
        encodeInteger(0x80, 7, index);
    } else {
        int staticTableIndex = mStaticTable->getIndexInsensitive(name, value);//HpackStaticTable.getIndexInsensitive(name, value);
        if (staticTableIndex != -1) {
            // Section 6.1. Indexed Header Field Representation
            encodeInteger(0x80, 7, staticTableIndex);
        } else {
            ensureCapacity(headerSize);
            encodeLiteral(name, value, st(HPack)::Incremental, getNameIndex(name));
            add(name, value, headerSize);
        }
    }
}

void _HPackEncoder::encodeInteger(int mask,int n,long i) {
    if(n >= 0 && n <= 8) {
        Trigger(IllegalArgumentException,"n is illegal");
    }

    int nbits = (unsigned int)0xFF >> (8 - n);
    if (i < nbits) {
        writer->writeByte((int) (mask | i));
    } else {
        writer->writeByte(mask | nbits);
        unsigned long length = i - nbits;
        for (; (length & ~0x7F) != 0; length >>= 7) {
            writer->writeByte((int) (length & 0x7F | 0x80));
        }
        writer->writeByte((int) length);
    }
}

void _HPackEncoder::encodeLiteral(String name,String value,int indexType,int nameIndex) {
    bool nameIndexValid = (nameIndex != -1);
    switch(indexType) {
        case st(HPack)::Incremental: {
            /*  6.2.1:Literal Header Field with Incremental Indexing
                Literal Header Field with Incremental Indexing -- Indexed Name
                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 0 | 1 |      Index (6+)       |
                +---+---+-----------------------+
                | H |     Value Length (7+)     |
                +---+---------------------------+
                | Value String (Length octets)  |
                +-------------------------------+

                Literal Header Field with Incremental Indexing -- New Name
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
            encodeInteger(0x40, 6, nameIndexValid ? nameIndex : 0);
            break;
        }

        case st(HPack)::None: {
            /*  6.2.2 Literal Header Field without Indexing
                Literal Header Field without Indexing -- Indexed Name
                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 0 | 0 | 0 | 0 |  Index (4+)   |
                +---+---+-----------------------+
                | H |     Value Length (7+)     |
                +---+---------------------------+
                | Value String (Length octets)  |
                +-------------------------------+

                Literal Header Field without Indexing -- New Name
                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 0 | 0 | 0 | 0 |       0       |
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
            encodeInteger(0x00, 4, nameIndexValid ? nameIndex : 0);
            break;
        }

        case st(HPack)::Never: {
            /*  6.2.3  Literal Header Field Never Indexed
                Literal Header Field Never Indexed -- Indexed Name
                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 0 | 0 | 0 | 1 |  Index (4+)   |
                +---+---+-----------------------+
                | H |     Value Length (7+)     |
                +---+---------------------------+
                | Value String (Length octets)  |
                +-------------------------------+

                Literal Header Field Never Indexed -- New Name
                  0   1   2   3   4   5   6   7
                +---+---+---+---+---+---+---+---+
                | 0 | 0 | 0 | 1 |       0       |
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
            encodeInteger(0x10, 4, nameIndexValid ? nameIndex : 0);
            break;
        }
    }

    if (!nameIndexValid) {
        encodeString(name);
    }
    encodeString(value);
}

void _HPackEncoder::encodeString(String data) {
    int huffmanLength;
    if (data->size() >= HuffCodeThreshold
            && (huffmanLength = mHuffEncoder->getEncodedLength(data)) < data->size()) {
        encodeInteger(0x80, 7, huffmanLength);
        mHuffEncoder->encode(writer, data);
    } else {
        encodeInteger(0x00, 7, data->size());
        //https://tools.ietf.org/html/rfc7540#section-8.1.2
        writer->writeByteArray(data->toByteArray());
    }
}

int _HPackEncoder::getNameIndex(String name) {
    HPackTableItem item = mStaticTable->get(name);
    if(item != nullptr) {
        return item->id;
    }

    //find in dynamic table
    int index = getIndex(name);
    if (index >= 0) {
        index += mStaticTable->size();
    }
    return -1;
}

int _HPackEncoder::getIndex(String name) {
    if (name == nullptr) {
        return -1;
    }

    int h = name->hashcode();
    int i = index(h);
    for (HPackEncoderEntry e = mEncoderEntries[i]; e != nullptr; e = e->next) {
        if (e->hash == h && name->equals(e->name)) {
            return getIndex(e->index);
        }
    }
    return -1;
}

int _HPackEncoder::getIndex(int index) {
    return index == -1 ? -1 : index - header->before->index + 1;
}

int _HPackEncoder::index(int h) {
    return h & mask;
}

HPackTableItem _HPackEncoder::getEntry(String name,String value) {
    int h = name->hashcode();
    int i = index(h);
    for (HPackEncoderEntry e = mEncoderEntries[i]; e != nullptr; e = e->next) {
        // Check the value before then name, as it is more likely the value will be different incase there is no
        // match.
        if (e->hash == h 
            && st(String)::contentEquals(value, e->value) 
            && st(String)::contentEquals(name, e->name)) {
            return e;
        }
    }
    return nullptr;
}

void _HPackEncoder::ensureCapacity(long headerSize) {
    while (maxHeaderTableSize - mSize < headerSize) {
        int index = size();
        if (index == 0) {
            break;
        }
        remove();
    }
}

void _HPackEncoder::add(String name, String value, long headerSize) {
    // Clear the table if the header field size is larger than the maxHeaderTableSize.
    if (headerSize > maxHeaderTableSize) {
        clear();
        return;
    }

    // Evict oldest entries until we have enough maxHeaderTableSize.
    while (maxHeaderTableSize - mSize < headerSize) {
        remove();
    }

    int h = name->hashcode();
    int i = index(h);
    HPackEncoderEntry old = mEncoderEntries[i];
    HPackEncoderEntry e = createHPackEncoderEntry(h, name, value, header->before->id - 1, old);
    mEncoderEntries[i] = e;
    e->addBefore(header);
    mSize += headerSize;
}

HPackEncoderEntry _HPackEncoder::remove() {
    if (mSize == 0) {
        return nullptr;
    }

    HPackEncoderEntry eldest = header->after;
    int h = eldest->hash;
    int i = index(h);
    HPackEncoderEntry prev = mEncoderEntries[i];
    HPackEncoderEntry e = prev;
    while (e != nullptr) {
        HPackEncoderEntry next = e->next;
        if (e == eldest) {
            if (prev == eldest) {
                mEncoderEntries[i] = next;
            } else {
                prev->next = next;
            }
            eldest->remove();
            mSize -= eldest->size();
            return eldest;
        }
        prev = e;
        e = next;
    }

    return nullptr;
}

void _HPackEncoder::clear() {
    mEncoderEntries = createList<HPackEncoderEntry>(maxDynamicTableSize);
    header = createHPackEncoderEntry(-1, "","",st(Integer)::MAX_VALUE, nullptr);
    header->before = header->after = header;
    mSize = 0;
}

int _HPackEncoder::size() {
    return mSize == 0 ? 0 : header->after->id - header->before->id + 1;
}

}