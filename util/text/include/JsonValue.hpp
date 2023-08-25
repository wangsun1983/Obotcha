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
#include "Text.hpp"

namespace obotcha {

class _JsonValue;

DECLARE_CLASS(JsonValueIterator) {
public:
    explicit _JsonValueIterator(const sp<_JsonValue> &value);

    String getTag();

    bool hasValue() const;

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

    int index = 0;

    int size;

    bool isArrayMember;
};

DECLARE_CLASS(JsonValue) {
public:
    friend class _JsonWriter;
    friend class _JsonReader;
    friend class _JsonValueIterator;

    _JsonValue() = default;

    explicit _JsonValue(const Json::Value &v, String name = nullptr);

    explicit _JsonValue(const sp<_JsonValue> &v, String name = nullptr);

    bool isBool() const;

    bool isInt() const;

    bool isUint64() const;

    bool isString() const;

    bool isDouble() const;

    bool isArray() const;

    bool isNull() const;

    bool isObject() const;

    // for value
    template <typename T>
    bool put(String tag,sp<T> value) {
        if(value != nullptr) {
            try {
                jvalue[tag->toChars()] = value->toValue();
                return true;
            } catch(Json::LogicError &err) {
                LOG(ERROR)<<"json value put ["<<tag->toChars()
                          <<"] failed,reason is "<<err.what();
            }
        }
        return false;
    }

    template <typename T>
    bool put(String tag,T value) {
        try {
            jvalue[tag->toChars()] = value;
            return true;
        } catch(Json::LogicError &err) {
            LOG(ERROR)<<"json value put ["<<tag->toChars()
                      <<"] failed,reason is "<<err.what();
        }
        return false;
    }

    bool put(String tag,sp<_JsonValue> value);

    // remove
    sp<_JsonValue> remove(String tag);

    sp<_JsonValue> removeAt(int);

    String getName() const;

    String getString(String tag) const;

    String getString(const char *valuetag) const;

    String getString() const;

    Integer getInteger(String tag) const;

    Integer getInteger(const char *tag) const;

    Integer getInteger() const;

    Uint64 getUint64(String tag) const;

    Uint64 getUint64(const char *tag) const;

    Uint64 getUint64() const;

    Long getLong(String tag) const;

    Long getLong(const char *tag) const;

    Long getLong() const;

    Boolean getBoolean(String tag) const;

    Boolean getBoolean(const char *) const;

    Boolean getBoolean() const;

    Double getDouble(String tag) const;

    Double getDouble(const char *tag) const;

    Double getDouble() const;

    sp<_JsonValue> getValue(String tag);

    sp<_JsonValue> getValue(const char *);

    sp<_JsonValueIterator> getIterator();

    bool contains(String tag) const;

    int size() const;

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

    String toString() override;

    bool isEmpty() const ;

    void reflectTo(Object obj,st(Text)::Syntax type = st(Text)::Syntax::Value);

    void importFrom(Object value); 

    ~_JsonValue() override = default;

private:

    String mName = nullptr;

    Json::Value jvalue;

    void reflectToArrayList(Object obj);
    void reflectToHashMap(Object obj);
    void importFromArrayList(String name,Object value);
    void importFromHashMap(String name,Object value);
};

} // namespace obotcha
#endif