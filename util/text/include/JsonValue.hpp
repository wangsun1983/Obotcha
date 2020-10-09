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

    String getString();

    Integer getInteger(String tag);

    Integer getInteger();

    Uint64 getUint64(String tag);

    Uint64 getUint64();

    Long getLong(String tag);

    Long getLong();

    Boolean getBoolean(String tag);

    Boolean getBoolean();

    Double getDouble(String tag);

    Double getDouble();

    sp<_JsonValue> getValue(String tag);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag);

    int size();

    //for array
    void append(String value);

    void append(const char *value);

    void append(std::string value);

    void append(Integer value);

    void append(Uint64 value);

    void append(int value);

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
            auto vv = field->createListItemObject();
            JsonValue value = this->getValueAt(index);
            value->reflectTo(vv);
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
                case FieldTypeLong:{
                    String value = jsonnode->getString();
                    field->setValue(value->toBasicLong());
                    }
                    break;

                case FieldTypeInt: {
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicInt());
                    }
                    break;

                case FieldTypeByte:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicByte());
                    }
                    break;

                case FieldTypeBool:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicBool());
                    }
                    break;

                case FieldTypeDouble:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicDouble());
                    }
                    break;

                case FieldTypeFloat:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicFloat());
                    }
                    break;

                case FieldTypeString:{
                        String value = jsonnode->getString();
                        field->setValue(value);
                    }
                    break;

                case FieldTypeUint8:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint8());
                    }
                    break;

                case FieldTypeUint16:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint16());
                    }
                    break;

                case FieldTypeUint32:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint32());
                    }
                    break;

                case FieldTypeUint64:{
                        String value = jsonnode->getString();
                        field->setValue(value->toBasicUint64());
                    }
                    break;
                        
                case FieldTypeObject: {
                        //create Objectt
                        field->createObject();
                        auto reflectValue = field->getObjectValue();
                        jsonnode->reflectTo(reflectValue);
                    }
                    break;

                case FieldTypeArrayList:
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
                case FieldTypeLong: {
                    this->put(name,field->getLongValue());
                }
                break;

                case FieldTypeInt: {
                    this->put(name,field->getIntValue());
                }
                break;

                case FieldTypeByte:{
                    this->put(name,field->getByteValue());
                }
                break;

                case FieldTypeBool:{
                    this->put(name,field->getBoolValue());
                }
                break;

                case FieldTypeDouble:{
                    this->put(name,field->getDoubleValue());
                }
                break;

                case FieldTypeFloat:{
                    this->put(name,field->getFloatValue());
                }
                break;

                case FieldTypeString:{
                    this->put(name,field->getStringValue());
                }
                break;

                case FieldTypeUint8:{
                    this->put(name,(uint64_t)field->getByteValue());
                }
                break;

                case FieldTypeUint16:{
                    this->put(name,(uint64_t)field->getUint16Value());
                }
                break;

                case FieldTypeUint32:{
                    this->put(name,(uint64_t)field->getUint32Value());
                }
                break;

                case FieldTypeUint64:{
                    this->put(name,(uint64_t)field->getUint32Value());
                }
                break;
                case FieldTypeObject: {
                    auto newObject = field->getObjectValue();
                    JsonValue newValue = createJsonValue();
                    newValue->importFrom(newObject);
                    this->put(name,newValue);
                }
                break;
                
                case FieldTypeArrayList: {
                    int count = 0;
                    JsonValue arrayNode = createJsonValue();
                    while(1) {
                        auto newObject = field->getListItemObject(count);
                        if(newObject != nullptr) {
                            JsonValue newValue = createJsonValue();
                            newValue->importFrom(newObject);
                            arrayNode->append(newValue);
                            count++;
                            continue;
                        }
                        break;
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