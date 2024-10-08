#include "HPackEncoder.hpp"
#include "IllegalArgumentException.hpp"
#include "HPack.hpp"
#include "HPackStaticTable.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "HPackSensitiveTable.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

//------HPackEncoderEntry------
_HPackEncoderEntry::_HPackEncoderEntry(uint64_t param_hash, 
                                       String param_name, 
                                       String param_value, 
                                       int param_counter, 
                                       HPackEncoderEntry param_next):
                                       next(param_next),hash(param_hash),
                                       counter(param_counter) {
    this->name = param_name;
    this->value = param_value;
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

_HPackEncoder::_HPackEncoder(bool param_ignoreMaxHeaderListSize,int tableSize):
                            ignoreMaxHeaderListSize(param_ignoreMaxHeaderListSize),
                            dynamicHeaderSize(tableSize) {
    int entriesLen = 128;
    mEncoderEntries = List<HPackEncoderEntry>::New(entriesLen);
    mask = entriesLen - 1;

    header = HPackEncoderEntry::New(-1, "","",st(Integer)::kMaxValue, nullptr);
    header->before = header->after = header;
    latest = header;
}

void _HPackEncoder::encodeHeaders(int streamId, ByteArrayWriter w, HttpHeader headers) {
    this->writer = w;
    if (ignoreMaxHeaderListSize) {
        encodeHeadersIgnoreMaxHeaderListSize(headers);
    } else {
        encodeHeadersEnforceMaxHeaderListSize(streamId,headers);
    }
}

void _HPackEncoder::encodeHeadersEnforceMaxHeaderListSize([[maybe_unused]]int param_streamId,
                                                          HttpHeader headers) {
    long headerSize = 0;
    // To ensure we stay consistent with our peer check the size is 
    // valid before we potentially modify HPACK state.
    auto iterator = headers->getIterator();
    while(iterator->hasValue()) {
        String name = iterator->getKey();
        String value = nullptr;
        auto v = iterator->getValue();
        if(IsInstance(String,v)) {
            value = v;
        } else {
            value = v->toString();
        }
        // OK to increment now and check for bounds after because this value is limited to unsigned int and will not
        // overflow.
        headerSize += st(HPackTableItem)::sizeOf(name, value);
        if (headerSize > maxHeaderListSize) {
            Trigger(ArrayIndexOutOfBoundsException,"over size")
        }

        iterator->next();
    }
    encodeHeadersIgnoreMaxHeaderListSize(headers);
}

void _HPackEncoder::encodeHeadersIgnoreMaxHeaderListSize(HttpHeader headers) {
    
    //check whether we encode status response
    //encode pseudo header first
    if(headers->getType() == st(Http)::PacketType::Response) {
        String status = String::New(headers->getResponseStatus());
        encodeHeader(st(HttpHeader)::Status, status, st(HPackSensitiveTable)::isSensitive(st(HttpHeader)::Status),
                        st(HPackTableItem)::sizeOf(st(HttpHeader)::Status, status));
    }

#define ProcessEncodePseduo(Header) \
   {\
        auto pseudoValue = headers->get(Header);\
        if(pseudoValue != nullptr) {\
            encodeHeader(Header, pseudoValue, st(HPackSensitiveTable)::isSensitive(Header),\
                            st(HPackTableItem)::sizeOf(Header, pseudoValue));\
        }\
    }

    ProcessEncodePseduo(st(HttpHeader)::Method)
    ProcessEncodePseduo(st(HttpHeader)::Status)
    ProcessEncodePseduo(st(HttpHeader)::Path)
    ProcessEncodePseduo(st(HttpHeader)::Scheme)
    ProcessEncodePseduo(st(HttpHeader)::Protocol)
    ProcessEncodePseduo(st(HttpHeader)::Authority)
#undef ProcessEncodePseduo

    auto iterator = headers->getIterator();
    while (iterator->hasValue()) {
        if(String name = iterator->getKey();!name->contains(":")) {
            if(!iterator->getKey()->equals(st(HttpHeader)::Version)) {  //version is not header
                String value = iterator->getValue()->toString();
                encodeHeader(name, value, st(HPackSensitiveTable)::isSensitive(name),
                                st(HPackTableItem)::sizeOf(name, value));
            }
        }
        iterator->next();
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
        if (int staticTableIndex = mStaticTable->getIndexInsensitive(name, value);
            staticTableIndex == -1) {
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
    HPackEncoderEntry headerField = getEntry(name, value);
    if (headerField != nullptr) {
        // Section 6.1. Indexed Header Field Representation
        encodeInteger(0x80, 7, getIndexPlusOffset(headerField->counter));
    } else {
        int staticTableIndex = mStaticTable->getIndexInsensitive(name, value);
        if (staticTableIndex != -1) {
            // Section 6.1. Indexed Header Field Representation
            encodeInteger(0x80, 7, staticTableIndex);
        } else {
            ensureCapacity(headerSize);
            int staticTableIndex = mStaticTable->getIndex(name);
            int nextCounter = latestCounter() - 1;
            if(staticTableIndex == -1) {
                auto entry = getEntry(name);
                if(entry == nullptr) {
                    encodeLiteral(name, value,st(HPack)::Incremental, -1 /**not found*/);
                    add(name,value,headerSize);
                } else {
                    encodeLiteral(name, value,st(HPack)::Incremental, getIndexPlusOffset(entry->counter));
                    add(name,value,headerSize);
                }
            } else {
                encodeLiteral(name, value, st(HPack)::Incremental, staticTableIndex);
                add(name,value,headerSize);
            }
            //add(name, value, headerSize);
        }
    }
}

void _HPackEncoder::encodeInteger(int mask,int n,long i) {
    if(n < 0 || n > 8) {
        Trigger(IllegalArgumentException,"n is illegal")
    }

    int nbits = (unsigned int)0xFF >> (8 - n);
    if (i < nbits) {
        writer->write<byte>(mask | i);
    } else {
        writer->write<byte>(mask | nbits);
        unsigned long length = i - nbits;
        for (; (length & ~0x7F) != 0; length >>= 7) {
            writer->write<byte>(length & 0x7F | 0x80);
        }
        writer->write<byte>(length);
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
    int huffmanLength = mHuffEncoder->getEncodedLength(data);
    if (data->size() >= HuffCodeThreshold
            && huffmanLength < data->size()) {
        encodeInteger(0x80, 7, huffmanLength);
        mHuffEncoder->encode(writer, data);
    } else {
        encodeInteger(0x00, 7, data->size());
        //https://tools.ietf.org/html/rfc7540#section-8.1.2
        writer->write(data->toByteArray());
    }
}

int _HPackEncoder::getNameIndex(String name) {
    if(HPackTableItem item = mStaticTable->get(name);
        item != nullptr) {
        return item->id;
    }

    //find in dynamic table
    int index = getIndex(name);
    if (index >= 0) {
        index += mStaticTable->size();
    }
    //TODO
    return -1;
}

int _HPackEncoder::getIndex(String name) {
    if (name == nullptr) {
        return -1;
    }

    auto h = name->hashcode();
    auto i = index(h);
    for (HPackEncoderEntry e = mEncoderEntries[i]; e != nullptr; e = e->next) {
        if (e->hash == h && name->equals(e->name)) {
            return getIndex(e->counter);
        }
    }
    return -1;
}

/**
 * Compute the index into the dynamic table given the counter in the header entry.
 */
int _HPackEncoder::getIndex(int counter) {
    return counter - latestCounter() + 1;
}

int _HPackEncoder::getIndexPlusOffset(int counter) {
    return getIndex(counter) + mStaticTable->size();
}

int _HPackEncoder::latestCounter() {
    return latest->counter;
}

uint64_t _HPackEncoder::index(uint64_t h) const {
    return h & mask;
}

HPackEncoderEntry _HPackEncoder::getEntry(String name) {
    uint64_t h = name->hashcode();
    uint64_t i = index(h);
    for (HPackEncoderEntry e = mEncoderEntries[i]; e != nullptr; e = e->next) {
        // Check the value before then name, as it is more likely the value will be different incase there is no
        // match.  
        if (e->hash == h
            && st(String)::Equals(name, e->name)) {
            return e;
        }
    }
    return nullptr;
}

HPackEncoderEntry _HPackEncoder::getEntry(String name,String value) {
    uint64_t h = name->hashcode();
    uint64_t i = index(h);
        
    for (HPackEncoderEntry e = mEncoderEntries[i]; e != nullptr; e = e->next) {
        // Check the value before then name, as it is more likely the value will be different incase there is no
        // match.
        if (e->hash == h
            && st(String)::Equals(value, e->value)
            && st(String)::Equals(name, e->name)) {
            return e;
        }
    }
    return nullptr;
}

void _HPackEncoder::ensureCapacity(long headerSize) {
    while (maxHeaderTableSize - mSize < headerSize) {
        if (size() == 0) {
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

    int nextCounter = latestCounter() - 1;

    uint64_t h = name->hashcode();
    uint64_t i = index(h);
    HPackEncoderEntry old = mEncoderEntries[i];
    HPackEncoderEntry e = HPackEncoderEntry::New(h, name, value, nextCounter, old);
    mEncoderEntries[i] = e;
    e->addBefore(header);
    mSize += headerSize;
    latest = e;
}

HPackEncoderEntry _HPackEncoder::remove() {
    if (mSize == 0) {
        return nullptr;
    }

    HPackEncoderEntry eldest = header->after;
    uint64_t h = eldest->hash;
    uint64_t i = index(h);
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
    mEncoderEntries = List<HPackEncoderEntry>::New(maxDynamicTableSize);
    header = HPackEncoderEntry::New(-1, "","",st(Integer)::kMaxValue, nullptr);
    header->before = header->after = header;
    mSize = 0;
}

int _HPackEncoder::size() const {
    return mSize == 0 ? 0 : header->after->id - header->before->id + 1;
}

_HPackEncoder::~_HPackEncoder() {
    auto size = mEncoderEntries->size();
    for(auto i = 0;i < size;i++) {
        auto entry = mEncoderEntries[i];
        if(entry != nullptr) {
            entry->remove();
        }
        mEncoderEntries[i] = nullptr;
    }
    mEncoderEntries = nullptr;

    header->before = nullptr;
    header->after = nullptr;
    header = nullptr;
}

}
