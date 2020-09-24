#ifndef __OBOTCHA_SQLITE3_CLIENT_H__
#define __OBOTCHA_SQLITE3_CLIENT_H__

#include "sqlite3.h"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "ReflectUtil.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(Sqlite3Client) {

public:
    int connect(HashMap<String, String> args);
    
    SqlRecords query(SqlQuery query);

    int count(String);

    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        String sql = query->toString();
        char **dbResult;
        int nRow, nColumn;
        char *errmsg = NULL;
        ArrayList<T> queryResult = createArrayList<T>();
        int result = sqlite3_get_table(mSqlDb, sql->toChars(), &dbResult, &nRow, &nColumn, &errmsg);
        if (SQLITE_OK == result) {
            int index = nColumn;
            for (int i = 0; i < nRow; i++) {
                T data;
                st(ReflectUtil)::createObject(data);
                for (int j = 0; j < nColumn; j++) {
                    //printf( “字段名:%s ?> 字段值:%s\n”, dbResult[j], dbResult [index] );
                    // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，
                    //从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
                    Field field = data->getField(createString(dbResult[j]));
                    if (field != nullptr) {
                        String value = createString(dbResult[index]);
                        switch (field->getType()) {
                            case FieldTypeLong: {
                                field->setValue(value->toBasicLong());
                            }
                            break;

                            case FieldTypeInt: {
                                field->setValue(value->toBasicInt());
                            }
                            break;

                            case FieldTypeByte: {
                                field->setValue(value->toBasicByte());
                            }
                            break;

                            case FieldTypeBool: {
                                field->setValue(value->toBasicBool());
                            }
                            break;

                            case FieldTypeDouble: {
                                field->setValue(value->toBasicDouble());
                            }
                            break;

                            case FieldTypeFloat: {
                                field->setValue(value->toBasicFloat());
                            }
                            break;

                            case FieldTypeString: {
                                field->setValue(value);
                            }
                            break;

                            case FieldTypeUint8: {
                                field->setValue(value->toBasicUint8());
                            }
                            break;

                            case FieldTypeUint16: {
                                field->setValue(value->toBasicUint16());
                            }
                            break;

                            case FieldTypeUint32: {
                                field->setValue(value->toBasicUint32());
                            }
                            break;

                            case FieldTypeUint64: {
                                field->setValue(value->toBasicUint64());
                            }
                            break;
                        }
                        index++;
                        
                    }
                }

                queryResult->add(data);
            }
            sqlite3_free_table(dbResult);
            return queryResult;
        }

        return nullptr;
    }

    int exec(SqlQuery);

    int close();

    int startTransaction();

    int commitTransaction();

    int rollabckTransaction();

private:
    sqlite3 *mSqlDb;

    String mPath;
};

} // namespace obotcha
#endif