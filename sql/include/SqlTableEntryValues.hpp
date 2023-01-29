#ifndef __OBOTCHA_SQL_TABLE_ENTRY_VALUES_H__
#define __OBOTCHA_SQL_TABLE_ENTRY_VALUES_H__

#include "Object.hpp"
#include "TextContent.hpp"
#include "HashMap.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

DECLARE_CLASS(SqlTableEntry) {
public:
    String name;
    String type;
    String constraint;
    int size;

    _SqlTableEntry(String name,String type,int size = 0,String constraint = nullptr);
};

DECLARE_CLASS(SqlTableEntryValues) {
public:
    _SqlTableEntryValues();
    void addEntry(String name,String type,int size = 0,String constraint = nullptr);
    String toString();
private:
    ArrayList<SqlTableEntry> mEntries;
};

} // namespace obotcha
#endif