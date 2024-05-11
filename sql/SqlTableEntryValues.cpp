#include "SqlTableEntryValues.hpp"
#include "ForEveryOne.hpp"
#include "StringBuffer.hpp"

namespace obotcha {

//SqlTableEntry
_SqlTableEntry::_SqlTableEntry(String name,String type,int size,String constraint) {
    this->name = name;
    this->type = type;
    this->constraint = constraint;
    this->size = size;
}

_SqlTableEntryValues::_SqlTableEntryValues() {
    mEntries = ArrayList<SqlTableEntry>::New();
}

void _SqlTableEntryValues::addEntry(String name,String type,int size,String constraint) {
    auto entry = SqlTableEntry::New(name,type,size,constraint);
    mEntries->add(entry);
}

String _SqlTableEntryValues::toString() {
    StringBuffer buffer = StringBuffer::New();
    ForEveryOne(entry,mEntries) {
        buffer->append(entry->name," ");
        buffer->append(entry->type," ");
        if(entry->size != 0) {
            buffer->append("(",String::New(entry->size),") ");
        }

        if(entry->constraint != nullptr) {
            buffer->append(entry->constraint);
        }

        buffer->append(",");
    }

    return buffer->subString(0,buffer->size() -1);
}


} // namespace obotcha
