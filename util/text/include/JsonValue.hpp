#ifndef __JSON_VALUE_H__
#define __JSON_VALUE_H__

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
class _JsonValueIterator;

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

    bool isString();

    bool isDouble();

    bool isArray();

    bool isObject();

    void put(String tag,String value);

    void put(String tag,const char *value);

    void put(String tag,std::string value);

    void put(String tag,Integer value);

    void put(String tag,int value);

    void put(String tag,Boolean value);

    void put(String tag,bool value);

    void put(String tag,Double value);

    void put(String tag,double value);

    void put(String tag,sp<_JsonValue> value);

    void put(sp<_JsonArray> value);

    void remove(String tag);

    String getString(String tag);

    String getString();

    Integer getInteger(String tag);

    Integer getInteger();

    Boolean getBoolean(String tag);

    Boolean getBoolean();

    Double getDouble(String tag);

    Double getDouble();

    sp<_JsonValue> getObject(String tag);

    sp<_JsonArray> getArray(String tag);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag);

    int size();

    ~_JsonValue();

private:
    Json::Value jvalue;    
};


DECLARE_SIMPLE_CLASS(JsonValueIterator) {
public:
    _JsonValueIterator(JsonValue value);

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

    sp<_JsonArray> getArray();

private:
    JsonValue value;

    Json::Value::Members mMembers;

    uint32_t count;
};

}
#endif