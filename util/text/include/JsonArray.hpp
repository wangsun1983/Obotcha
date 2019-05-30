#ifndef __JSON_ARRAY_H__
#define __JSON_ARRAY_H__

#include "json/value.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "Boolean.hpp"
#include "Integer.hpp"
#include "Float.hpp"
#include "Long.hpp"

namespace obotcha {

class _JsonValue;
class _JsonWriter;

DECLARE_SIMPLE_CLASS(JsonArray) {
public:
    friend class _JsonValue;
    friend class _JsonWriter;
    friend class _JsonReader;

    _JsonArray(String s);

    _JsonArray(String s,Json::Value v);

    void append(String value);

    void append(char *value);

    void append(std::string value);

    void append(Integer value);

    void append(int value);

    void append(Boolean value);

    void append(bool value);

    void append(Double value);

    void append(double value);

    void append(sp<_JsonValue> value);

    String getName();

    sp<_JsonValue> getValue(int index);

    int size();

    ~_JsonArray();

private:
    Json::Value jvalue;
    String name;
};

}
#endif