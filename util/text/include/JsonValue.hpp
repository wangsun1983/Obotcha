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
    template <typename T>
    void put(String tag,sp<T> value) {
        if(value != nullptr) {
            jvalue[tag->toChars()] = value->toValue();
        }
    }

    template <typename T>
    void put(String tag,T value) {
        jvalue[tag->toChars()] = value;
    }

    void put(String tag,sp<_JsonValue> value);

    // remove
    sp<_JsonValue> remove(String tag);

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
    template <typename T>
    void append(sp<T> value) {
        jvalue.append(value->toValue());
    }

    template <typename T>
    void append(T value) {
        jvalue.append(value);
    }
    
    void append(sp<_JsonValue> value);
    
    sp<_JsonValue> getValueAt(int index);

    sp<_JsonValue> getListItemAt(unsigned int index);

    String getStringAt(int index);

    Integer getIntegerAt(int index);

    Boolean getBooleanAt(int index);

    Double getDoubleAt(int index);

    String toString();

    bool isEmpty();

    void reflectTo(Object obj,int type = ReflectValue);

    void importFrom(Object value); 

    ~_JsonValue();
private:
    enum ReflectType{
        ReflectValue = 0,
        ReflectName,
    };

    String mName;

    Json::Value jvalue;

    void reflectToArrayList(Object obj);
    void reflectToHashMap(Object obj);
    void importFromArrayList(String name,Object value);
    void importFromHashMap(String name,Object value);
};

} // namespace obotcha
#endif