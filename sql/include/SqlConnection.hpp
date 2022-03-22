#ifndef __OBOTCHA_SQL_CONNECTION_HPP__
#define __OBOTCHA_SQL_CONNECTION_HPP__

#include <map>
#include "String.hpp"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "ArrayList.hpp"
#include "SqlConnectParam.hpp"
#include <functional>

namespace obotcha {

class _MySqlConnection;
class _Sqlite3Connection;

using onRowStartCallback = std::function<void()>;
using onRowNewDataCallback = std::function<void(String,String)>;
using onRowEndCallback = std::function<void()>;

DECLARE_CLASS(SqlConnection) {

public:
    enum ConnectionType {
        MySqlConnection = 0,
        Sqlite3Connection,
    };

    _SqlConnection();

    virtual int exec(SqlQuery query){return -1;}
    
    virtual SqlRecords query(SqlQuery query){return nullptr;}

    virtual int connect(SqlConnectParam args){return -1;}

    virtual int count(SqlQuery query) {return -1;}

    virtual int close(){return -1;}

    virtual int startTransaction(){return -1;}

    virtual int commitTransaction(){return -1;}

    virtual int rollabckTransaction(){return -1;}
    
    template <typename T>
    ArrayList<T> query(SqlQuery query) {
        ArrayList<T> result = createArrayList<T>();
        T dataset;
        printf("sql start query \n");
        queryWithEachRow(query,
            [&dataset]() {
                printf("sql start query,on start \n");
                st(ReflectUtil)::createObject(dataset);
            },

            [&dataset](String name,String value) {
                printf("sql start query,on data,name is %s,value is %s \n",name->toChars(),value->toChars());
                Field field = dataset->getField(name);
                if (field != nullptr) {
                    switch (field->getType()) {
                        case st(Field)::FieldTypeLong: {
                            field->setValue(value->toBasicLong());
                        }
                        break;

                        case st(Field)::FieldTypeInt: {
                            field->setValue(value->toBasicInt());
                        }
                        break;

                        //case st(Field)::FieldTypeByte: {
                        //    field->setValue(value->toBasicByte());
                        //}
                        //break;

                        case st(Field)::FieldTypeBool: {
                            field->setValue(value->toBasicBool());
                        }
                        break;

                        case st(Field)::FieldTypeDouble: {
                            field->setValue(value->toBasicDouble());
                        }
                        break;

                        case st(Field)::FieldTypeFloat: {
                            field->setValue(value->toBasicFloat());
                        }
                        break;

                        case st(Field)::FieldTypeString: {
                            field->setValue(value);
                        }
                        break;

                        case st(Field)::FieldTypeUint8: {
                            field->setValue(value->toBasicUint8());
                        }
                        break;

                        case st(Field)::FieldTypeUint16: {
                            field->setValue(value->toBasicUint16());
                        }
                        break;

                        case st(Field)::FieldTypeUint32: {
                            field->setValue(value->toBasicUint32());
                        }
                        break;

                        case st(Field)::FieldTypeUint64: {
                            field->setValue(value->toBasicUint64());
                        }
                        break;
                    }
                }
            },
            [&dataset,&result]() {
                printf("sql finis query \n");
                result->add(dataset);
                printf("result size is %d \n",result->size());
            }
        );
        
        return result;
    }

protected:
    int mType;

    virtual void onRowStart() {};
    virtual void onRowNewData(String name,String value){};
    virtual void onRowEnd(){};

    virtual void queryWithEachRow(SqlQuery query,onRowStartCallback,onRowNewDataCallback,onRowEndCallback){};

};

}

#endif