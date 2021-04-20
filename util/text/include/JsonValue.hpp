#ifndef __OBOTCHA_JSON_VALUE_H__
#define __OBOTCHA_JSON_VALUE_H__

#include "json/value.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Float.hpp"
#include "Long.hpp"
#include "Uint32.hpp"
#include "ArrayList.hpp"
#include "Field.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "OStdInstanceOf.hpp"

namespace obotcha {

class _JsonArray;
class _JsonValue;

DECLARE_SIMPLE_CLASS(JsonValueIterator) {
public:
    _JsonValueIterator(sp<_JsonValue> value);

    _JsonValueIterator(_JsonValue *value);

    String getTag();

    bool hasValue();

    bool isBool();

    bool isInt();

    bool isString();

    bool isDouble();

    bool isArray();

    bool isObject();

    bool next();

    sp<_JsonValue> getValue();

    String getString();

    Integer getInteger();

    Boolean getBoolean();

    Double getDouble();

    sp<_JsonValue> getObject();

private:
    sp<_JsonValue> value;

    Json::Value::Members mMembers;

    uint32_t count;
};


DECLARE_SIMPLE_CLASS(JsonValue) {

public:
    friend class _JsonArray;
    friend class _JsonWriter;
    friend class _JsonReader;
    friend class _JsonValueIterator;

    _JsonValue();

    _JsonValue(Json::Value v);

    _JsonValue(sp<_JsonValue> v);

    bool isBool();

    bool isInt();

    bool isUint64();

    bool isString();

    bool isDouble();

    bool isArray();

    bool isNull();

    bool isObject();
    
    //for value
    void put(String tag,String value);

    void put(String tag,const char *value);

    void put(String tag,std::string value);

    void put(String tag,Integer value);

    void put(String tag,int value);

    void put(String tag,Boolean value);

    void put(String tag,bool value);

    void put(String tag,Double value);

    void put(String tag,double value);

    void put(String tag,Uint64 value);

    void put(String tag,uint64_t value);

    void put(String tag,long value);

    void put(String tag,sp<_JsonValue> value);

    void remove(String tag);

    //remove
    void removeAt(int);

    String getString(String tag);

    String getString(const char* valuetag);
    
    String getString();

    Integer getInteger(String tag);

    Integer getInteger(const char* tag);

    Integer getInteger();

    Uint64 getUint64(String tag);

    Uint64 getUint64(const char* tag);

    Uint64 getUint64();

    Long getLong(String tag);
    
    Long getLong(const char * tag);

    Long getLong();

    Boolean getBoolean(String tag);

    Boolean getBoolean(const char *);

    Boolean getBoolean();

    Double getDouble(String tag);

    Double getDouble(const char* tag);

    Double getDouble();

    sp<_JsonValue> getValue(String tag);

    sp<_JsonValue> getValue(const char *);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag);

    int size();

    //for array
    void append(String value);

    void append(const char *value);

    void append(std::string value);

    void append(Integer value);

    void append(int value);

    void append(Long value);

    void append(long value);

    void append(Uint8 value);

    void append(uint8_t value);

    void append(Uint16 value);

    void append(uint16_t value);

    void append(Uint32 value);

    void append(uint32_t value);
    
    void append(Uint64 value);

    void append(uint64_t value);

    void append(Boolean value);

    void append(bool value);

    void append(Double value);

    void append(double value);

    void append(sp<_JsonValue> value);

    sp<_JsonValue> getValueAt(int index);

    String getStringAt(int index);
    
    Integer getIntegerAt(int index);

    Boolean getBooleanAt(int index);

    Double getDoubleAt(int index);

    String toString();

    template<typename T>
    void reflectToArrayList(T obj,String name) {
        Field field = obj->getField(name);
        field->createObject();
        int size = this->size();
        for(int index = 0;index<size;index++) {
            auto newObject = field->createListItemObject();
            JsonValue value = this->getValueAt(index);
            if(IsInstance(Integer,newObject)) {
                Integer data = Cast<Integer>(newObject);
                data->update(value->getInteger()->toValue());
            } else if(IsInstance(Long,newObject)) {
                Long data = Cast<Long>(newObject);
                data->update(value->getLong()->toValue());
            } else if(IsInstance(Boolean,newObject)) {
                Boolean data = Cast<Boolean>(newObject);
                data->update(value->getBoolean()->toValue());
            } else if(IsInstance(Double,newObject)) {
                Double data = Cast<Double>(newObject);
                data->update(value->getDouble()->toValue());
            } else if(IsInstance(Float,newObject)) {
                Float data = Cast<Float>(newObject);
                data->update(value->getDouble()->toValue());
            } else if(IsInstance(Byte,newObject)) {
                Byte data = Cast<Byte>(newObject);
                data->update(value->getUint64()->toValue());
            } else if(IsInstance(Uint8,newObject)) {
                Uint8 data = Cast<Uint8>(newObject);
                data->update(value->getUint64()->toValue());
            } else if(IsInstance(Uint16,newObject)) {
                Uint16 data = Cast<Uint16>(newObject);
                data->update(value->getUint64()->toValue());
            } else if(IsInstance(Uint32,newObject)) {
                Uint32 data = Cast<Uint32>(newObject);
                data->update(value->getUint64()->toValue());
            } else if(IsInstance(Uint64,newObject)) {
                Uint64 data = Cast<Uint64>(newObject);
                data->update(value->getUint64()->toValue());
            } else if(IsInstance(String,newObject)) {
                String data = Cast<String>(newObject);
                data->update(value->getString()->getStdString());
            } else {
                value->reflectTo(newObject);
            }
        }
    }

    template<typename T>
    void reflectTo(T obj) {
        sp<_JsonValueIterator> iterator = this->getIterator();
        while(iterator->hasValue()) {
            String key = iterator->getTag();
            Field field = obj->getField(key);
            if(field == nullptr) {
                iterator->next();
                continue;
            }
            std::string name = field->getName()->getStdString();
            JsonValue jsonnode = iterator->getValue();
            switch(field->getType()) {
                case st(Field)::FieldTypeLong:{
                    String value = jsonnode->getString();
                    field->setValue(value->toBasicLong());
                    }
                    break;

                case st(Field)::FieldTypeInt: {
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicInt());
                    }
                    break;

                case st(Field)::FieldTypeByte:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicByte());
                    }
                    break;

                case st(Field)::FieldTypeBool:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicBool());
                    }
                    break;

                case st(Field)::FieldTypeDouble:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicDouble());
                    }
                    break;

                case st(Field)::FieldTypeFloat:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicFloat());
                    }
                    break;

                case st(Field)::FieldTypeString:{
                        String value = jsonnode->getString();
                        field->setValue(value);
                    }
                    break;

                //case st(Field)::FieldTypeUint8:{
                //        String value = jsonnode->getString();
                //        field->setValue(value->toBasicUint8());
                //    }
                //    break;

                case st(Field)::FieldTypeUint16:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint16());
                    }
                    break;

                case st(Field)::FieldTypeUint32:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint32());
                    }
                    break;

                case st(Field)::FieldTypeUint64:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint64());
                    }
                    break;
                        
                case st(Field)::FieldTypeObject: {
                        //create Objectt
                        sp<_Object> newObject = field->createObject();
                        auto reflectValue = field->getObjectValue();
                        if(IsInstance(Integer,newObject)) {
                            String value = jsonnode->getString();
                            Integer data = Cast<Integer>(newObject);
                            data->update(value->toBasicInt());
                        } else if(IsInstance(Long,newObject)) {
                            String value = jsonnode->getString();
                            Long data = Cast<Long>(newObject);
                            data->update(value->toBasicLong());
                        } else if(IsInstance(Boolean,newObject)) {
                            String value = jsonnode->getString();
                            Boolean data = Cast<Boolean>(newObject);
                            data->update(value->toBasicBool());
                        } else if(IsInstance(Double,newObject)) {
                            String value = jsonnode->getString();
                            Double data = Cast<Double>(newObject);
                            data->update(value->toBasicDouble());
                        } else if(IsInstance(Float,newObject)) {
                            String value = jsonnode->getString();
                            Float data = Cast<Float>(newObject);
                            data->update(value->toBasicFloat());
                        } else if(IsInstance(Byte,newObject)) {
                            String value = jsonnode->getString();
                            Byte data = Cast<Byte>(newObject);
                            data->update(value->toBasicByte());
                        } else if(IsInstance(Uint8,newObject)) {
                            String value = jsonnode->getString();
                            Uint8 data = Cast<Uint8>(newObject);
                            data->update(value->toBasicUint8());
                        } else if(IsInstance(Uint16,newObject)) {
                            String value = jsonnode->getString();
                            Uint16 data = Cast<Uint16>(newObject);
                            data->update(value->toBasicUint16());
                        } else if(IsInstance(Uint32,newObject)) {
                            String value = jsonnode->getString();
                            Uint32 data = Cast<Uint32>(newObject);
                            data->update(value->toBasicUint32());
                        } else if(IsInstance(Uint64,newObject)) {
                            String value = jsonnode->getString();
                            Uint64 data = Cast<Uint64>(newObject);
                            data->update(value->toBasicUint64());
                        } else {
                            printf("reflect to name is %s \n",field->getName()->toChars());
                            jsonnode->reflectTo(reflectValue);
                        }
                    }
                    break;

                case st(Field)::FieldTypeArrayList:
                    jsonnode->reflectToArrayList(obj,field->getName());
                    break;
            }

            iterator->next();
        }
    }

    template<typename T>
    void importFrom(T value) {
        ArrayList<Field> fields = value->getAllFields();
        if(fields == nullptr) {
            LOG(ERROR)<<"fields is nullptr !!!!!";
        }
        ListIterator<Field> iterator = fields->getIterator();
        while(iterator->hasValue()) {
            Field field = iterator->getValue();
            String name = field->getName();
            switch(field->getType()) {
                case st(Field)::FieldTypeLong: {
                    this->put(name,field->getLongValue());
                }
                break;

                case st(Field)::FieldTypeInt: {
                    this->put(name,field->getIntValue());
                }
                break;

                //case st(Field)::FieldTypeByte:{
                //    this->put(name,field->getByteValue());
                //}
                //break;

                case st(Field)::FieldTypeBool:{
                    this->put(name,field->getBoolValue());
                }
                break;

                case st(Field)::FieldTypeDouble:{
                    this->put(name,field->getDoubleValue());
                }
                break;

                case st(Field)::FieldTypeFloat:{
                    this->put(name,field->getFloatValue());
                }
                break;

                case st(Field)::FieldTypeString:{
                    this->put(name,field->getStringValue());
                }
                break;

                case st(Field)::FieldTypeUint8:{
                    this->put(name,(uint64_t)field->getByteValue());
                }
                break;

                case st(Field)::FieldTypeUint16:{
                    this->put(name,(uint64_t)field->getUint16Value());
                }
                break;

                case st(Field)::FieldTypeUint32:{
                    this->put(name,(uint64_t)field->getUint32Value());
                }
                break;

                case st(Field)::FieldTypeUint64:{
                    this->put(name,(uint64_t)field->getUint64Value());
                }
                break;

                case st(Field)::FieldTypeObject: {
                    //check whether it is Number
                    auto newObject = field->getObjectValue();
                    JsonValue newValue = createJsonValue();
                    if(IsInstance(Integer,newObject)) {
                        Integer data = Cast<Integer>(newObject);
                        this->put(name,data->toValue());
                    } else if(IsInstance(Long,newObject)) {
                        Long data = Cast<Long>(newObject);
                        this->put(name,data->toValue());
                    } else if(IsInstance(Boolean,newObject)) {
                        Boolean data = Cast<Boolean>(newObject);
                        this->put(name,data->toValue());
                    } else if(IsInstance(Double,newObject)) {
                        Double data = Cast<Double>(newObject);
                        this->put(name,data->toValue());
                    } else if(IsInstance(Float,newObject)) {
                        Float data = Cast<Float>(newObject);
                        this->put(name,data->toValue());
                    } else if(IsInstance(Byte,newObject)) {
                        Byte data = Cast<Byte>(newObject);
                        this->put(name,(uint64_t)data->toValue());
                    } else if(IsInstance(Uint8,newObject)) {
                        Uint8 data = Cast<Uint8>(newObject);
                        this->put(name,(uint64_t)data->toValue());
                    } else if(IsInstance(Uint16,newObject)) {
                        Uint16 data = Cast<Uint16>(newObject);
                        this->put(name,(uint64_t)data->toValue());
                    } else if(IsInstance(Uint32,newObject)) {
                        Uint32 data = Cast<Uint32>(newObject);
                        this->put(name,(uint64_t)data->toValue());
                    } else if(IsInstance(Uint64,newObject)) {
                        Uint64 data = Cast<Uint64>(newObject);
                        this->put(name,(uint64_t)data->toValue());
                    } else if(IsInstance(String,newObject)) {
                        String data = Cast<String>(newObject);
                        this->put(name,data->getStdString());
                    } else {
                        printf("field name is %s \n",field->getName()->toChars());
                        newValue->importFrom(newObject);
                        this->put(name,newValue);
                    }
                }
                break;
                
                case st(Field)::FieldTypeArrayList: {
                    int count = 0;
                    int size = field->getListObjectSize();
                    JsonValue arrayNode = createJsonValue();
                    while(count < size) {
                        auto newObject = field->getListItemObject(count);
                        if(newObject != nullptr) {
                            if(IsInstance(Integer,newObject)) {
                                Integer data = Cast<Integer>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Long,newObject)) {
                                Long data = Cast<Long>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Boolean,newObject)) {
                                Boolean data = Cast<Boolean>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Double,newObject)) {
                                Double data = Cast<Double>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Float,newObject)) {
                                Float data = Cast<Float>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Byte,newObject)) {
                                Byte data = Cast<Byte>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Uint8,newObject)) {
                                Uint8 data = Cast<Uint8>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Uint16,newObject)) {
                                Uint16 data = Cast<Uint16>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Uint32,newObject)) {
                                Uint32 data = Cast<Uint32>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(Uint64,newObject)) {
                                Uint64 data = Cast<Uint64>(newObject);
                                arrayNode->append(data->toValue());
                            } else if(IsInstance(String,newObject)) {
                                String data = Cast<String>(newObject);
                                arrayNode->append(data->toChars());
                            } else {
                                JsonValue newValue = createJsonValue();
                                newValue->importFrom(newObject);
                                arrayNode->append(newValue);
                            }
                        }
                        count++;
                    }
                    this->put(name,arrayNode);
                }
                break;
            }
            iterator->next();
        }        
    }

    ~_JsonValue();

private:
    String mTag;

    Json::Value jvalue;    
};



}
#endif