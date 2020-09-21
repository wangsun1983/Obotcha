#include "SqlRecords.hpp"

namespace obotcha {

bool _SqlRecordsIterator::hasValue() {
    return (index >= records->getRowNum());
}

List<String> _SqlRecordsIterator::getRowData() {
    return records->mRecords[index];
}

List<String> _SqlRecordsIterator::next() {
    index++;
    return records->mRecords[index-1];
}

int _SqlRecords::getRowNum() {
    return rows;
}

int _SqlRecords::getColumnNum() {
    return columns;
}

_SqlRecords::_SqlRecords(int row,int col) {
    rows = row;
    columns = col;
    mRecords = createList<List<String>>(row);
}

void _SqlRecords::setOneRow(int index,List<String> list) {
    mRecords[index] = list;
}


}