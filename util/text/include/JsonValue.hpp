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
    sp<T> createObjectFromArrayList(ArrayList<T> value) {
        sp<T> data;
        T *p = new T();
        p->__ReflectInit();
        data.set_pointer(p);
        return data;
    }

    template<typename T>
    void reflectTo(T obj) {
        if(this->isArray()) {
            //we should create arraylist
            
            obj->createFieldValue(mTag->getStdString());
            sp<_JsonValueIterator> iterator = this->getIterator();
            ArrayList<sp<Object>> listvalue = (ArrayList<sp<Object>>)obj->getFieldObjectValue(mTag->getStdString());
            while(iterator->hasValue()) {
                auto vv = createObjectFromArrayList(listvalue);
                JsonValue jsonnode = iterator->getValue();
                reflectTo(vv,jsonnode);
                listvalue->add(vv);
                iterator->next();
            }
        } else {
            sp<_JsonValueIterator> iterator = this->getIterator();
            while(iterator->hasValue()) {
                String key = iterator->getTag();
                
                Field field = obj->getField(key);
                if(field == nullptr) {
                    printf("key is %s \n",key->toChars());
                    iterator->next();
                    continue;
                }
                std::string name = field->getName()->getStdString();
                JsonValue jsonnode = iterator->getValue();

                switch(field->getType()) {
                    case FieldTypeInt: {
                            String value = jsonnode->getString();
                            obj->setFieldIntValue(name,value->toBasicInt());
                        }
                        break;

                    case FieldTypeByte:{
                            String value = jsonnode->getString();
                            obj->setFieldByteValue(name,value->toBasicByte());
                        }
                        break;

                    
                    case FieldTypeBool:{
                            String value = jsonnode->getString();
                            obj->setFieldBoolValue(name,value->toBasicBool());
                        }
                        break;

                    case FieldTypeDouble:{
                            String value = jsonnode->getString();
                            obj->setFieldDoubleValue(name,value->toBasicDouble());
                        }
                        break;

                    case FieldTypeFloat:{
                            String value = jsonnode->getString();
                            obj->setFieldFloatValue(name,value->toBasicFloat());
                        }
                        break;

                    case FieldTypeString:{
                            String value = jsonnode->getString();
                            obj->setFieldStringValue(name,value->getStdString());
                        }
                        break;

                    case FieldTypeUint8:{
                            String value = jsonnode->getString();
                            obj->setFieldUint8Value(name,value->toBasicUint8());
                        }
                        break;

                    case FieldTypeUint16:{
                            String value = jsonnode->getString();
                            obj->setFieldUint16Value(name,value->toBasicUint16());
                        }
                        break;

                    case FieldTypeUint32:{
                            String value = jsonnode->getString();
                            obj->setFieldUint32Value(name,value->toBasicUint32());
                        }
                        break;

                    case FieldTypeUint64:{
                            String value = jsonnode->getString();
                            obj->setFieldUint64Value(name,value->toBasicUint64());
                        }
                        break;
                         
                    case FieldTypeObject: {
                            //create Objectt
                            printf("createobj name is %s\n",name.c_str());
                            obj->createFieldValue(name);
                            auto reflectValue = obj->getFieldObjectValue(name);
                            if(reflectValue != nullptr) {
                                printf("create obj not null \n");
                            } else {
                                printf("create obj null \n");
                            }
                            jsonnode->reflectTo(reflectValue);
                        }
                        break;

                    case FieldTypeArrayList:
                        //TODO
                        break;
                }

                iterator->next();
            }
        }
    }

    ~_JsonValue();

private:
    String mTag;

    Json::Value jvalue;    
};



}
#endif