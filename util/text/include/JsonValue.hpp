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
            if (IsInstance(Integer, newObject)) {
                Integer data = Cast<Integer>(newObject);
                data->update(value->getInteger()->toValue());
            } else if (IsInstance(Long, newObject)) {
                Long data = Cast<Long>(newObject);
                data->update(value->getLong()->toValue());
            } else if (IsInstance(Boolean, newObject)) {
                Boolean data = Cast<Boolean>(newObject);
                data->update(value->getBoolean()->toValue());
            } else if (IsInstance(Double, newObject)) {
                Double data = Cast<Double>(newObject);
                data->update(value->getDouble()->toValue());
            } else if (IsInstance(Float, newObject)) {
                Float data = Cast<Float>(newObject);
                data->update(value->getDouble()->toValue());
            } else if (IsInstance(Byte, newObject)) {
                Byte data = Cast<Byte>(newObject);
                data->update(value->getUint64()->toValue());
            } else if (IsInstance(Uint8, newObject)) {
                Uint8 data = Cast<Uint8>(newObject);
                data->update(value->getUint64()->toValue());
            } else if (IsInstance(Uint16, newObject)) {
                Uint16 data = Cast<Uint16>(newObject);
                data->update(value->getUint64()->toValue());
            } else if (IsInstance(Uint32, newObject)) {
                Uint32 data = Cast<Uint32>(newObject);
                data->update(value->getUint64()->toValue());
            } else if (IsInstance(Uint64, newObject)) {
                Uint64 data = Cast<Uint64>(newObject);
                data->update(value->getUint64()->toValue());
            } else if (IsInstance(String, newObject)) {
                String data = Cast<String>(newObject);
                data->update(value->getString()->getStdString());
            } else if (newObject->__ReflectClassName()->equals("_ArrayList")) {
                value->reflectToArrayList(newObject);
            } else if (newObject->__ReflectClassName()->equals("_HashMap")) {
                value->reflectToHashMap(newObject);
            } else {
                value->reflectTo(newObject);
            }
            obj->__addListItemObject("", newObject);
        }
    }

    template <typename T> void reflectToHashMap(T obj) {
        sp<_JsonValueIterator> iterator = this->getIterator();
        while (iterator->hasValue()) {
            JsonValue jvalue = iterator->getValue();
            String tag = iterator->getTag();
            KeyValuePair<Object, Object> pair = obj->__createMapItemObject("");

            Object key = pair->getKey();
            if (IsInstance(Integer, key)) {
                Integer data = Cast<Integer>(key);
                data->update(tag->toBasicInt());
            } else if (IsInstance(Long, key)) {
                Long data = Cast<Long>(key);
                data->update(tag->toBasicLong());
            } else if (IsInstance(Boolean, key)) {
                Boolean data = Cast<Boolean>(key);
                data->update(tag->toBasicBool());
            } else if (IsInstance(Double, key)) {
                Double data = Cast<Double>(key);
                data->update(tag->toBasicDouble());
            } else if (IsInstance(Float, key)) {
                Float data = Cast<Float>(key);
                data->update(tag->toBasicFloat());
            } else if (IsInstance(Byte, key)) {
                Byte data = Cast<Byte>(key);
                data->update(tag->toBasicByte());
            } else if (IsInstance(Uint8, key)) {
                Uint8 data = Cast<Uint8>(key);
                data->update(tag->toBasicUint8());
            } else if (IsInstance(Uint16, key)) {
                Uint16 data = Cast<Uint16>(key);
                data->update(tag->toBasicUint16());
            } else if (IsInstance(Uint32, key)) {
                Uint32 data = Cast<Uint32>(key);
                data->update(tag->toBasicUint32());
            } else if (IsInstance(Uint64, key)) {
                Uint64 data = Cast<Uint64>(key);
                data->update(tag->toBasicUint64());
            } else if (IsInstance(String, key)) {
                String data = Cast<String>(key);
                data->update(tag->toChars());
            } else {
                Trigger(TransformException, "not support key type");
            }

            Object pairValue = pair->getValue();
            if (IsInstance(Integer, pairValue)) {
                Integer data = Cast<Integer>(pairValue);
                data->update(jvalue->getInteger()->toValue());
            } else if (IsInstance(Long, pairValue)) {
                Long data = Cast<Long>(pairValue);
                data->update(jvalue->getLong()->toValue());
            } else if (IsInstance(Boolean, pairValue)) {
                Boolean data = Cast<Boolean>(pairValue);
                data->update(jvalue->getBoolean()->toValue());
            } else if (IsInstance(Double, pairValue)) {
                Double data = Cast<Double>(pairValue);
                data->update(jvalue->getDouble()->toValue());
            } else if (IsInstance(Float, pairValue)) {
                Float data = Cast<Float>(pairValue);
                data->update(jvalue->getDouble()->toValue());
            } else if (IsInstance(Byte, pairValue)) {
                Byte data = Cast<Byte>(pairValue);
                data->update(jvalue->getUint64()->toValue());
            } else if (IsInstance(Uint8, pairValue)) {
                Uint8 data = Cast<Uint8>(pairValue);
                data->update(jvalue->getUint64()->toValue());
            } else if (IsInstance(Uint16, pairValue)) {
                Uint16 data = Cast<Uint16>(pairValue);
                data->update(jvalue->getUint64()->toValue());
            } else if (IsInstance(Uint32, pairValue)) {
                Uint32 data = Cast<Uint32>(pairValue);
                data->update(jvalue->getUint64()->toValue());
            } else if (IsInstance(Uint64, pairValue)) {
                Uint64 data = Cast<Uint64>(pairValue);
                data->update(jvalue->getUint64()->toValue());
            } else if (IsInstance(String, pairValue)) {
                String data = Cast<String>(pairValue);
                data->update(jvalue->getString()->getStdString());
            } else if (pairValue->__ReflectClassName()->equals("_ArrayList")) {
                int datasize = jvalue->size();
                for (int index = 0; index < datasize; index++) {
                    JsonValue oo = jvalue->getListItemAt(index);
                    Object vv = pairValue->__createListItemObject("");
                    oo->reflectTo(vv);
                    pairValue->__addListItemObject("", vv);
                }
            } else if (pairValue->__ReflectClassName()->equals("_HashMap")) {
                jvalue->reflectToHashMap(pairValue);
            } else {
                jvalue->reflectTo(pairValue);
            }
            obj->__addMapItemObject("", key, pairValue);
            iterator->next();
        }
    }

    template <typename T> void reflectTo(T obj) {
        if (obj->__ReflectClassName()->equals("_ArrayList")) {
            reflectToArrayList(obj);
            return;
        } else if (obj->__ReflectClassName()->equals("_HashMap")) {
            reflectToHashMap(obj);
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
                String value = jsonnode->getString();
                field->setValue(value->toBasicLong());
            } break;

            case st(Field)::FieldTypeInt: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicInt());
            } break;

            case st(Field)::FieldTypeByte: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicByte());
            } break;

            case st(Field)::FieldTypeBool: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicBool());
            } break;

            case st(Field)::FieldTypeDouble: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicDouble());
            } break;

            case st(Field)::FieldTypeFloat: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicFloat());
            } break;

            case st(Field)::FieldTypeString: {
                String value = jsonnode->getString();
                field->setValue(value);
            } break;

            case st(Field)::FieldTypeUint16: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicUint16());
            } break;

            case st(Field)::FieldTypeUint32: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicUint32());
            } break;

            case st(Field)::FieldTypeUint64: {
                String value = jsonnode->getString();
                field->setValue(value->toBasicUint64());
            } break;

            case st(Field)::FieldTypeObject: {
                // create Objectt
                sp<_Object> newObject = field->createObject();
                //auto reflectValue = field->getObjectValue();
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
                    jsonnode->reflectTo(newObject);
                }
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
    void importFrom(sp<_JsonValue> jsonNode,
                    ArrayList<KeyValuePair<Object, Object>> members) {
        // ArrayList<KeyValuePair<Object,Object>> members =
        // field->getMapItemObjects();
        int count = 0;
        int size = members->size();

        while (count < size) {
            KeyValuePair<Object, Object> pair = members->get(count);
            Object key = pair->getKey();
            String keyStr = nullptr;

            if (key != nullptr) {
                if (IsInstance(Integer, key)) {
                    Integer data = Cast<Integer>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Long, key)) {
                    Long data = Cast<Long>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Boolean, key)) {
                    Boolean data = Cast<Boolean>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Double, key)) {
                    Double data = Cast<Double>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Float, key)) {
                    Float data = Cast<Float>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Byte, key)) {
                    Byte data = Cast<Byte>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Uint8, key)) {
                    Uint8 data = Cast<Uint8>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Uint16, key)) {
                    Uint16 data = Cast<Uint16>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Uint32, key)) {
                    Uint32 data = Cast<Uint32>(key);
                    keyStr = createString(data);
                } else if (IsInstance(Uint64, key)) {
                    Uint64 data = Cast<Uint64>(key);
                    keyStr = createString(data);
                } else if (IsInstance(String, key)) {
                    String data = Cast<String>(key);
                    keyStr = createString(data);
                } else {
                    Trigger(TransformException, "not support key type");
                }
            }

            Object value = pair->getValue();
            JsonValue mapItemNode = createJsonValue();
            if (value != nullptr) {
                if (IsInstance(Integer, value)) {
                    Integer data = Cast<Integer>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Long, value)) {
                    Long data = Cast<Long>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Boolean, value)) {
                    Boolean data = Cast<Boolean>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Double, value)) {
                    Double data = Cast<Double>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Float, value)) {
                    Float data = Cast<Float>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Byte, value)) {
                    Byte data = Cast<Byte>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Uint8, value)) {
                    Uint8 data = Cast<Uint8>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Uint16, value)) {
                    Uint16 data = Cast<Uint16>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(Uint32, value)) {
                    Uint32 data = Cast<Uint32>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, (uint64_t)data->toValue());
                } else if (IsInstance(Uint64, value)) {
                    Uint64 data = Cast<Uint64>(value);
                    // mapItemNode->append(data->toValue());
                    jsonNode->put(keyStr, data->toValue());
                } else if (IsInstance(String, value)) {
                    String data = Cast<String>(value);
                    // mapItemNode->append(data->toChars());
                    jsonNode->put(keyStr, data->toChars());
                } else {
                    JsonValue newValue = createJsonValue();
                    newValue->importFrom(value);
                    jsonNode->put(keyStr, newValue);
                }
            }
            // arrayNode->put(keyStr,mapItemNode);
            count++;
        }
    }

    template <typename T> void importFrom(T value) {
        if (value->__ReflectClassName()->equals("_ArrayList")) {
            int size = value->__getContainerSize("");
            this->jvalue.resize(size);
            for (int i = 0; i < size; i++) {
                auto newObject = value->__getListItemObject("", i);
                // newValue->importFrom(nValue);
                if (IsInstance(Integer, newObject)) {
                    Integer data = Cast<Integer>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Long, newObject)) {
                    Long data = Cast<Long>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Boolean, newObject)) {
                    Boolean data = Cast<Boolean>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Double, newObject)) {
                    Double data = Cast<Double>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Float, newObject)) {
                    Float data = Cast<Float>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Byte, newObject)) {
                    Byte data = Cast<Byte>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Uint8, newObject)) {
                    Uint8 data = Cast<Uint8>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Uint16, newObject)) {
                    Uint16 data = Cast<Uint16>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Uint32, newObject)) {
                    Uint32 data = Cast<Uint32>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(Uint64, newObject)) {
                    Uint64 data = Cast<Uint64>(newObject);
                    this->jvalue[i] = data->toValue();
                } else if (IsInstance(String, newObject)) {
                    String data = Cast<String>(newObject);
                    // this->put(name,data->getStdString());
                    this->jvalue[i] = data->getStdString();
                } else {
                    JsonValue newValue = createJsonValue();
                    newValue->importFrom(newObject);
                    // this->put(name,newValue);
                    this->jvalue[i] = newValue->jvalue;
                }
                // this->append(newValue);
            }
            return;
        } else if (value->__ReflectClassName()->equals("_HashMap")) {
            int size = value->__getContainerSize("");
            // JsonValue mapItemValue = createJsonValue();
            ArrayList<KeyValuePair<Object, Object>> members =
                value->__getMapItemObjects("");
            importFrom(AutoClone(this), members);
            // this->append(mapItemValue);
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

                // case st(Field)::FieldTypeByte:{
                //    this->put(name,field->getByteValue());
                //}
                // break;

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
                JsonValue newValue = createJsonValue();
                if (IsInstance(Integer, newObject)) {
                    Integer data = Cast<Integer>(newObject);
                    this->put(name, data->toValue());
                } else if (IsInstance(Long, newObject)) {
                    Long data = Cast<Long>(newObject);
                    this->put(name, data->toValue());
                } else if (IsInstance(Boolean, newObject)) {
                    Boolean data = Cast<Boolean>(newObject);
                    this->put(name, data->toValue());
                } else if (IsInstance(Double, newObject)) {
                    Double data = Cast<Double>(newObject);
                    this->put(name, data->toValue());
                } else if (IsInstance(Float, newObject)) {
                    Float data = Cast<Float>(newObject);
                    this->put(name, data->toValue());
                } else if (IsInstance(Byte, newObject)) {
                    Byte data = Cast<Byte>(newObject);
                    this->put(name, (uint64_t)data->toValue());
                } else if (IsInstance(Uint8, newObject)) {
                    Uint8 data = Cast<Uint8>(newObject);
                    this->put(name, (uint64_t)data->toValue());
                } else if (IsInstance(Uint16, newObject)) {
                    Uint16 data = Cast<Uint16>(newObject);
                    this->put(name, (uint64_t)data->toValue());
                } else if (IsInstance(Uint32, newObject)) {
                    Uint32 data = Cast<Uint32>(newObject);
                    this->put(name, (uint64_t)data->toValue());
                } else if (IsInstance(Uint64, newObject)) {
                    Uint64 data = Cast<Uint64>(newObject);
                    this->put(name, (uint64_t)data->toValue());
                } else if (IsInstance(String, newObject)) {
                    String data = Cast<String>(newObject);
                    this->put(name, data->getStdString());
                } else {
                    newValue->importFrom(newObject);
                    this->put(name, newValue);
                }
            } break;

            case st(Field)::FieldTypeArrayList: {
                int count = 0;
                int size = field->getContainerSize();
                JsonValue arrayNode = createJsonValue();
                while (count < size) {
                    auto newObject = field->getListItemObject(count);
                    if (newObject != nullptr) {
                        if (IsInstance(Integer, newObject)) {
                            Integer data = Cast<Integer>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Long, newObject)) {
                            Long data = Cast<Long>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Boolean, newObject)) {
                            Boolean data = Cast<Boolean>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Double, newObject)) {
                            Double data = Cast<Double>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Float, newObject)) {
                            Float data = Cast<Float>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Byte, newObject)) {
                            Byte data = Cast<Byte>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Uint8, newObject)) {
                            Uint8 data = Cast<Uint8>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Uint16, newObject)) {
                            Uint16 data = Cast<Uint16>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Uint32, newObject)) {
                            Uint32 data = Cast<Uint32>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(Uint64, newObject)) {
                            Uint64 data = Cast<Uint64>(newObject);
                            arrayNode->append(data->toValue());
                        } else if (IsInstance(String, newObject)) {
                            String data = Cast<String>(newObject);
                            arrayNode->append(data->toChars());
                        } else if (newObject->__ReflectClassName()->equals(
                                       "_ArrayList")) {
                            int size = newObject->__getContainerSize("");
                            JsonValue arrayItemValue = createJsonValue();
                            arrayItemValue->importFrom(newObject);
                            arrayNode->append(arrayItemValue);
                        } else if (newObject->__ReflectClassName()->equals(
                                       "_HashMap")) {
                            int size = newObject->__getContainerSize("");
                            JsonValue mapItemValue = createJsonValue();
                            auto members = newObject->__getMapItemObjects("");
                            importFrom(mapItemValue, members);
                            arrayNode->append(mapItemValue);
                        } else {
                            JsonValue newValue = createJsonValue();
                            newValue->importFrom(newObject);
                            arrayNode->append(newValue);
                        }
                    }
                    count++;
                }
                this->put(name, arrayNode);
            } break;

            case st(Field)::FieldTypeHashMap: {
                int count = 0;
                int size = field->getContainerSize();
                JsonValue mapNode = createJsonValue();
                ArrayList<KeyValuePair<Object, Object>> members =
                    field->getMapItemObjects();
                importFrom(mapNode, members);
                this->put(name, mapNode);
            } break;
            }
            iterator->next();
        }
    }

    ~_JsonValue();

private:
    String mName;

    Json::Value jvalue;
};

} // namespace obotcha
#endif