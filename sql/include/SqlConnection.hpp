#ifndef __OBOTCHA_SQL_CONNECTION_HPP__
#define __OBOTCHA_SQL_CONNECTION_HPP__

#include <functional>

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "SqlConnectParam.hpp"
#include "ReflectUtil.hpp"
#include "Field.hpp"
#include "SqlQuery.hpp"
#include "SqlRecords.hpp"
#include "SqlContentValues.hpp"
#include "SqlTableEntryValues.hpp"

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
    
    int create(String table,SqlTableEntryValues);
    int insert(String table,SqlContentValues);
    int update(String table,SqlContentValues,SqlQuery condition);
    int erase(String table,SqlQuery condition);
    
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
        queryWithEachRow(query,
            [&dataset]() {
                st(ReflectUtil)::createObject(dataset);
            },

            [&dataset](String name,String value) {
                Field field = dataset->getField(name);
                if (field != nullptr && value != nullptr) {
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

                        case st(Field)::FieldTypeObject: {
                            Object o = field->createObject();
                            if (IsInstance(Integer, o)) {
                                Cast<Integer>(o)->update(value->toBasicInt());
                            } else if (IsInstance(Long, o)) {
                                Cast<Long>(o)->update(value->toBasicLong());
                            } else if (IsInstance(Boolean, o)) {
                                Cast<Boolean>(o)->update(value->toBasicBool());
                            } else if (IsInstance(Double, o)) {
                                Cast<Double>(o)->update(value->toBasicDouble());
                            } else if (IsInstance(Float, o)) {
                                Cast<Float>(o)->update(value->toBasicFloat());
                            } else if (IsInstance(Byte, o)) {
                                Cast<Byte>(o)->update(value->toBasicByte());
                            } else if (IsInstance(Uint8, o)) {
                                Cast<Uint8>(o)->update(value->toBasicUint8());
                            } else if (IsInstance(Uint16, o)) {
                                Cast<Uint16>(o)->update(value->toBasicUint16());
                            } else if (IsInstance(Uint32, o)) {
                                Cast<Uint32>(o)->update(value->toBasicUint32());
                            } else if (IsInstance(Uint64, o)) {
                                Cast<Uint64>(o)->update(value->toBasicUint64());
                            } else if (IsInstance(String, o)) {
                                Cast<String>(o)->update(value->toChars());
                            }
                        }
                        break;
                    }
                }
            },
            [&dataset,&result]() {
                result->add(dataset);
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