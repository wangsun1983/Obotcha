#ifndef __OBOTCHA_SQL_RECORDS_H__
#define __OBOTCHA_SQL_RECORDS_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "List.hpp"

namespace obotcha {

class _SqlRecords;
class _SqlRecordsIterator;

DECLARE_SIMPLE_CLASS(SqlRecordsIterator) {
public:
    friend class _SqlRecords;

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

    _SqlRecords(int row,int col);

    int getRowNum();

    int getColumnNum();
    
    void setOneRow(int index,List<String>);

    sp<_SqlRecordsIterator> getIterator();
private:
    List<List<String>> mRecords;
    int rows;
    int columns;
};

} // namespace obotcha
#endif