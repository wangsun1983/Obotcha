#ifndef __OBOTCHA_JSON_VALUE_H__
#define __OBOTCHA_JSON_VALUE_H__

#include "json/value.h"

#include "ArrayList.hpp"
#include "Boolean.hpp"
#include "Field.hpp"
#include "Float.hpp"
#include "Integer.hpp"
#include "Log.hpp"
#include "Long.hpp"
#include "OStdInstanceOf.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "TransformException.hpp"
#include "Uint32.hpp"

namespace obotcha {

class _JsonArray;
class _JsonValue;

DECLARE_CLASS(JsonValueIterator) {
public:
    _JsonValueIterator(sp<_JsonValue> value);

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

    uint32_t index;

    uint32_t size;

    bool isArrayMember;
};

DECLARE_CLASS(JsonValue) {
public:
    friend class _JsonArray;
    friend class _JsonWriter;
    friend class _JsonReader;
    friend class _JsonValueIterator;

    _JsonValue();

    _JsonValue(Json::Value v, String name = nullptr);

    _JsonValue(sp<_JsonValue> v, String name = nullptr);

    bool isBool();

    bool isInt();

    bool isUint64();

    bool isString();

    bool isDouble();

    bool isArray();

    bool isNull();

    bool isObject();

    // for value
    void put(String tag, String value);

    void put(String tag, const char *value);

    void put(String tag, std::string value);

    void put(String tag, Integer value);

    void put(String tag, int value);

    void put(String tag, Boolean value);

    void put(String tag, bool value);

    void put(String tag, Double value);

    void put(String tag, double value);

    void put(String tag, Uint64 value);

    void put(String tag, uint64_t value);

    void put(String tag, Long value);

    void put(String tag, long value);

    void put(String tag, sp<_JsonValue> value);

    sp<_JsonValue> remove(String tag);

    // remove
    sp<_JsonValue> removeAt(int);

    String getName();

    String getString(String tag);

    String getString(const char *valuetag);

    String getString();

    Integer getInteger(String tag);

    Integer getInteger(const char *tag);

    Integer getInteger();

    Uint64 getUint64(String tag);

    Uint64 getUint64(const char *tag);

    Uint64 getUint64();

    Long getLong(String tag);

    Long getLong(const char *tag);

    Long getLong();

    Boolean getBoolean(String tag);

    Boolean getBoolean(const char *);

    Boolean getBoolean();

    Double getDouble(String tag);

    Double getDouble(const char *tag);

    Double getDouble();

    sp<_JsonValue> getValue(String tag);

    sp<_JsonValue> getValue(const char *);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag);

    int size();

    // for array
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

    sp<_JsonValue> getListItemAt(unsigned int index);

    String getStringAt(int index);

    Integer getIntegerAt(int index);

    Boolean getBooleanAt(int index);

    Double getDoubleAt(int index);

    String toString();

    bool isEmpty();

    template <typename T> void reflectToArrayList(T obj) {
        int size = this->size();
        for (int index = 0; index < size; index++) {
            auto newObject = obj->__createListItemObject("");
            JsonValue value = this->getListItemAt(index);
            value->reflectTo(newObject);
            obj->__addListItemObject("", newObject);
        }
    }

    template <typename T> void reflectToHashMap(T obj) {
        sp<_JsonValueIterator> iterator = this->getIterator();
        while (iterator->hasValue()) {
            JsonValue jvalue = iterator->getValue();
            String tag = iterator->getTag();
            Pair<Object, Object> pair = obj->__createMapItemObject("");

            Object key = pair->getKey();
            jvalue->reflectTo(key,ReflectName);

            Object pairValue = pair->getValue();
            jvalue->reflectTo(pairValue);

            obj->__addMapItemObject("", key, pairValue);
            iterator->next();
        }
    }

    template <typename T> void reflectTo(T obj,int type = ReflectValue) {
        //if it is a Lang/Container class
        try {
            if (obj->__ReflectClassName()->equals("_ArrayList")) {
                reflectToArrayList(obj);
                return;
            } else if (obj->__ReflectClassName()->equals("_HashMap")) {
                reflectToHashMap(obj);
                return;
            }
        } catch(...){} 

        if (IsInstance(Integer, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Integer>(obj)->update(v->toBasicInt());
            return;
        } else if (IsInstance(Long, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Long>(obj)->update(v->toBasicLong());
            return;
        } else if (IsInstance(Boolean, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Boolean>(obj)->update(v->toBasicBool());
            return;
        } else if (IsInstance(Double, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Double>(obj)->update(v->toBasicDouble());
            return;
        } else if (IsInstance(Float, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Float>(obj)->update(v->toBasicFloat());
            return;
        } else if (IsInstance(Byte, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Byte>(obj)->update(v->toBasicByte());
            return;
        } else if (IsInstance(Uint8, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Uint8>(obj)->update(v->toBasicUint8());
            return;
        } else if (IsInstance(Uint16, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Uint16>(obj)->update(v->toBasicUint16());
            return;
        } else if (IsInstance(Uint32, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Uint32>(obj)->update(v->toBasicUint32());
            return;
        } else if (IsInstance(Uint64, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<Uint64>(obj)->update(v->toBasicUint64());
            return;
        } else if (IsInstance(String, obj)) {
            String v = (type == ReflectValue)?this->getString():this->getName();
            Cast<String>(obj)->update(v->toChars());
            return;
        }

        sp<_JsonValueIterator> iterator = this->getIterator();
        while (iterator->hasValue()) {
            String key = iterator->getTag();
            Field field = obj->getField(key);
            if (field == nullptr) {
                iterator->next();
                continue;
            }
            std::string name = field->getName()->getStdString();
            JsonValue jsonnode = iterator->getValue();
            switch (field->getType()) {
                case st(Field)::FieldTypeLong: {
                    field->setValue(jsonnode->getString()->toBasicLong());
                } break;

                case st(Field)::FieldTypeInt: {
                    field->setValue(jsonnode->getString()->toBasicInt());
                } break;

                case st(Field)::FieldTypeByte: {
                    field->setValue(jsonnode->getString()->toBasicByte());
                } break;

                case st(Field)::FieldTypeBool: {
                    field->setValue(jsonnode->getString()->toBasicBool());
                } break;

                case st(Field)::FieldTypeDouble: {
                    field->setValue(jsonnode->getString()->toBasicDouble());
                } break;

                case st(Field)::FieldTypeFloat: {
                    field->setValue(jsonnode->getString()->toBasicFloat());
                } break;

                case st(Field)::FieldTypeString: {
                    field->setValue(jsonnode->getString());
                } break;

                case st(Field)::FieldTypeUint16: {
                    field->setValue(jsonnode->getString()->toBasicUint16());
                } break;

                case st(Field)::FieldTypeUint32: {
                    field->setValue(jsonnode->getString()->toBasicUint32());
                } break;

                case st(Field)::FieldTypeUint64: {
                    field->setValue(jsonnode->getString()->toBasicUint64());
                } break;

                case st(Field)::FieldTypeObject: {
                    // create Objectt
                    sp<_Object> newObject = field->createObject();
                    jsonnode->reflectTo(newObject);
                } break;

                case st(Field)::FieldTypeArrayList: {
                    Object newObject = field->createObject();
                    jsonnode->reflectToArrayList(newObject);
                } break;

                case st(Field)::FieldTypeHashMap: {
                    Object newObject = field->createObject();
                    jsonnode->reflectToHashMap(newObject);
                } break;
            }
            iterator->next();
        }
    }

    // wangsl
    template <typename T> void importFromArrayList(String name,T value) {
        int size = value->__getContainerSize("");
        JsonValue arrayNode = nullptr;
        if(name != nullptr) {
            arrayNode = createJsonValue();
        } else {
            arrayNode = AutoClone(this);
        }

        //arrayNode->jvalue.resize(size);

        for (int i = 0; i < size; i++) {
            JsonValue item = createJsonValue();
            auto newObject = value->__getListItemObject("", i);
            item->importFrom(newObject);
            arrayNode->append(item);
        }

        if(name != nullptr) {
            this->put(name, arrayNode);
        }
    }

    template <typename T> void importFromHashMap(String name,T value) {
        int size = value->__getContainerSize("");
        ArrayList<Pair<Object, Object>> members = value->__getMapItemObjects("");
        JsonValue mapItems = nullptr;

        if(name != nullptr){
            mapItems = createJsonValue();
        } else {
            mapItems = AutoClone(this);
        }

        for (int i = 0;i< size;i++) {
            Pair<Object, Object> pair = members->get(i);
            Object key = pair->getKey();
            Object value = pair->getValue();
            JsonValue newValue = createJsonValue();
            newValue->importFrom(value);

            String keyStr = nullptr;
            if (IsInstance(Integer, key)) {
                keyStr = createString(Cast<Integer>(key));
            } else if (IsInstance(Long, key)) {
                keyStr = createString(Cast<Long>(key));
            } else if (IsInstance(Boolean, key)) {
                keyStr = createString(Cast<Boolean>(key));
            } else if (IsInstance(Double, key)) {
                keyStr = createString(Cast<Double>(key));
            } else if (IsInstance(Float, key)) {
                keyStr = createString(Cast<Float>(key));
            } else if (IsInstance(Byte, key)) {
                keyStr = createString(Cast<Byte>(key));
            } else if (IsInstance(Uint8, key)) {
                keyStr = createString(Cast<Uint8>(key));
            } else if (IsInstance(Uint16, key)) {
                keyStr = createString(Cast<Uint16>(key));
            } else if (IsInstance(Uint32, key)) {
                keyStr = createString(Cast<Uint32>(key));
            } else if (IsInstance(Uint64, key)) {
                keyStr = createString(Cast<Uint64>(key));
            } else if (IsInstance(String, key)) {
                keyStr = Cast<String>(key);
            }

            if(keyStr != nullptr) {
                mapItems->put(keyStr, newValue);
            }
        }

        if(name != nullptr) {
            this->put(name,mapItems);
        }
    }

    template <typename T> void importFrom(T value) {
        try {
            if (value->__ReflectClassName()->equals("_ArrayList")) {
                importFromArrayList(nullptr,value);
                return;
            } else if (value->__ReflectClassName()->equals("_HashMap")) {
                importFromHashMap(nullptr,value);
                return;
            }
        } catch(...){}

        if (IsInstance(Integer, value)) {
            jvalue = Cast<Integer>(value)->toValue();
            return;
        } else if (IsInstance(Long, value)) {
            jvalue = Cast<Long>(value)->toValue();
            return;
        } else if (IsInstance(Boolean, value)) {
            jvalue = Cast<Boolean>(value)->toValue();
            return;
        } else if (IsInstance(Double, value)) {
            jvalue = Cast<Double>(value)->toValue();
            return;
        } else if (IsInstance(Float, value)) {
            jvalue = Cast<Float>(value)->toValue();
            return;
        } else if (IsInstance(Byte, value)) {
            jvalue = (uint64_t)(Cast<Byte>(value)->toValue());
            return;
        } else if (IsInstance(Uint8, value)) {
            jvalue = (uint64_t)(Cast<Uint8>(value)->toValue());
            return;
        } else if (IsInstance(Uint16, value)) {
            jvalue = (uint64_t)(Cast<Uint16>(value)->toValue());
            return;
        } else if (IsInstance(Uint32, value)) {
            jvalue = (uint64_t)(Cast<Uint32>(value)->toValue());
            return;
        } else if (IsInstance(Uint64, value)) {
            jvalue = (uint64_t)(Cast<Uint64>(value)->toValue());
            return;
        } else if (IsInstance(String, value)) {
            jvalue = Cast<String>(value)->getStdString();
            return;
        }

        ArrayList<Field> fields = value->getAllFields();
        if (fields == nullptr) {
            LOG(ERROR) << "import class has no reflect filed";
            return;
        }
        ListIterator<Field> iterator = fields->getIterator();
        while (iterator->hasValue()) {
            Field field = iterator->getValue();
            String name = field->getName();
            switch (field->getType()) {
                case st(Field)::FieldTypeLong: {
                    this->put(name, field->getLongValue());
                } break;

                case st(Field)::FieldTypeInt: {
                    this->put(name, field->getIntValue());
                } break;

                case st(Field)::FieldTypeBool: {
                    this->put(name, field->getBoolValue());
                } break;

                case st(Field)::FieldTypeDouble: {
                    this->put(name, field->getDoubleValue());
                } break;

                case st(Field)::FieldTypeFloat: {
                    this->put(name, field->getFloatValue());
                } break;

                case st(Field)::FieldTypeString: {
                    this->put(name, field->getStringValue());
                } break;

                case st(Field)::FieldTypeUint8: {
                    this->put(name, (uint64_t)field->getByteValue());
                } break;

                case st(Field)::FieldTypeUint16: {
                    this->put(name, (uint64_t)field->getUint16Value());
                } break;

                case st(Field)::FieldTypeUint32: {
                    this->put(name, (uint64_t)field->getUint32Value());
                } break;

                case st(Field)::FieldTypeUint64: {
                    this->put(name, (uint64_t)field->getUint64Value());
                } break;

                case st(Field)::FieldTypeObject: {
                    // check whether it is Number
                    auto newObject = field->getObjectValue();
                    if(newObject != nullptr) {
                        JsonValue newValue = createJsonValue();
                        newValue->importFrom(newObject);
                        this->put(name, newValue);
                    }
                }break;

                case st(Field)::FieldTypeArrayList: {
                    auto newObject = field->getObjectValue();
                    if(newObject != nullptr) {
                        importFromArrayList(name,newObject);
                    }
                } break;

                case st(Field)::FieldTypeHashMap: {
                    auto newObject = field->getObjectValue();
                    if(newObject != nullptr) {
                        importFromHashMap(name,newObject);
                    }
                } break;
            }
            iterator->next();
        }
    }

    ~_JsonValue();

private:
    enum ReflectType{
        ReflectValue = 0,
        ReflectName,
    };

    String mName;

    Json::Value jvalue;
};

} // namespace obotcha
#endif