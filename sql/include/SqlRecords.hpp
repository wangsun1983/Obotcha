#ifndef __OBOTCHA_SQL_RECORDS_H__
#define __OBOTCHA_SQL_RECORDS_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "List.hpp"

namespace obotcha {

class _SqlRecords;

DECLARE_SIMPLE_CLASS(SqlRecordsIterator) {
public:
    bool hasValue();

    List<String>getRowData();

    List<String>next();
private:
    sp<_SqlRecords> records;

    int index;
};

DECLARE_SIMPLE_CLASS(SqlRecords) {
public:
    friend class _SqlRecordsIterator;

    int getRowNum();

    int getColumnNum();
    
    void setOneRow(int index,List<String>);
    
    _SqlRecords(int row,int col);
private:
    List<List<String>> mRecords;
    int rows;
    int columns;
};

} // namespace obotcha
#endif