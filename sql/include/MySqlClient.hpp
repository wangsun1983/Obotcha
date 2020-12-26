#ifndef __OBOTCHA_MY_SQL_CLIENT_H__
#define __OBOTCHA_MY_SQL_CLIENT_H__

#include "mysql.h"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"
#include "Reflect.hpp"
#include "ReflectUtil.hpp"
#include "List.hpp"
#include "ReflectUtil.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"

namespace obotcha
{

DECLARE_SIMPLE_CLASS(MySqlClient)
{
public:
    int connect(HashMap<String, String> args);
    
    SqlRecords query(SqlQuery query);

    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        String sql = query->toString();
        int ret = mysql_real_query(&mysql, sql->toChars(),sql->size());
        if(ret == 0) {
            MYSQL_RES *res = nullptr;
            res = mysql_store_result(&mysql);
            int columnNum = mysql_num_fields(res);
            List<String> columns = createList<String>(columnNum);
            if (res != nullptr) {
                for(int i=0; i < columnNum; i++) {
                    MYSQL_FIELD *field = mysql_fetch_field_direct(res,i);
                    columns[i] = createString(field->name);
                }
                
                ArrayList<T> results = createArrayList<T>();
                MYSQL_ROW row;
                while ((row = mysql_fetch_row(res))) {
                    T objvalue;
                    st(ReflectUtil)::createObject(objvalue);

                    for (int i = 0; i < columnNum; i++) {
                        String val = createString(row[i]);
                        Field field = objvalue->getField(columns[i]);
                        switch(field->getType()) {
                            case st(Field)::FieldTypeLong:{
                                field->setValue(val->toBasicLong());
                            }
                            break;

                            case st(Field)::FieldTypeInt: {
                                field->setValue(val->toBasicInt());
                            }
                            break;

                            //case st(Field)::FieldTypeByte:{
                            //    field->setValue(val->toBasicByte());
                            //}
                            //break;

                            case st(Field)::FieldTypeBool:{
                                field->setValue(val->toBasicBool());
                            }
                            break;

                            case st(Field)::FieldTypeDouble:{
                                field->setValue(val->toBasicDouble());
                            }
                            break;

                            case st(Field)::FieldTypeFloat:{
                                field->setValue(val->toBasicFloat());
                            }
                            break;

                            case st(Field)::FieldTypeString:{
                                field->setValue(val);
                            }
                            break;

                            case st(Field)::FieldTypeUint8:{
                                field->setValue(val->toBasicUint8());
                            }
                            break;

                            case st(Field)::FieldTypeUint16:{
                                field->setValue(val->toBasicUint16());
                            }
                            break;

                            case st(Field)::FieldTypeUint32:{
                                field->setValue(val->toBasicUint32());
                            }
                            break;

                            case st(Field)::FieldTypeUint64:{
                                field->setValue(val->toBasicUint64());
                            }
                            break;
                        }
                    }

                    results->add(objvalue);
                }
                return results;
            }
            mysql_free_result(res);
        }  
        return nullptr;
    }

    int exec(SqlQuery);

    int close();

    int startTransaction();

    int commitTransaction();

    int rollabckTransaction();

private:
    MYSQL mysql;
};

} // namespace obotcha
#endif