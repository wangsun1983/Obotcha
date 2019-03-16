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

    void put(String tag,String value);

    void put(String tag,char *value);

    void put(String tag,std::string value);

    void put(String tag,Integer value);

    void put(String tag,int value);

    void put(String tag,Boolean value);

    void put(String tag,bool value);

    void put(String tag,Double value);

    void put(String tag,double value);

    void put(sp<_JsonArray> value);

    String getString(String tag);

    Integer getInteger(String tag);

    Boolean getBoolean(String tag);

    Double getDouble(String tag);

    sp<_JsonValue> getObject(String tag);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag);

    ~_JsonValue();

private:
    Json::Value *jvalue;    
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

    bool next();

private:
    JsonValue value;

    int count;
};

}
#endif