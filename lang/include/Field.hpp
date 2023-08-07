#ifndef __OBOTCHA_FIELD_HPP__
#define __OBOTCHA_FIELD_HPP__

#include "ArrayList.hpp"
#include "ByteArray.hpp"
#include "HashMap.hpp"
#include "Pair.hpp"
#include "Object.hpp"
#include "String.hpp"
#include <functional>
#include <vector>

namespace obotcha {

template <typename T> class _FieldContent;

DECLARE_CLASS(Field) {
public:
    enum {
        FieldTypeInt = 0,
        FieldTypeByte,
        FieldTypeDouble,
        FieldTypeFloat,
        FieldTypeLong,
        FieldTypeString,
        FieldTypeUint16,
        FieldTypeUint32,
        FieldTypeUint64,
        FieldTypeBool,
        FieldTypeVector, //??
        FieldTypeArrayList,
        FieldTypeHashMap,
        FieldTypeObject,
        FieldTypeUnKnow,
    };

    _Field();
    // wangsl
    static const int FieldTypeUint8 = FieldTypeByte;

    int TypeOf(int v) const;
    int TypeOf(byte v) const;
    int TypeOf(double v) const;
    int TypeOf(float v) const;
    int TypeOf(bool v) const;
    int TypeOf(long v) const;
    int TypeOf(uint16_t v) const;
    int TypeOf(uint32_t v) const;
    int TypeOf(uint64_t v) const;
    int TypeOf(String v) const;

    template <typename T> int TypeOf([[maybe_unused]] std::vector<T> v) const {
        return FieldTypeVector;
    }

    template <typename T> int TypeOf([[maybe_unused]] ArrayList<T> v) const {
        return FieldTypeArrayList;
    }

    template <typename T, typename U> int TypeOf([[maybe_unused]] HashMap<T, U> v) const {
        return FieldTypeHashMap;
    }

    template <typename T> int TypeOf([[maybe_unused]] T v) const { 
        return FieldTypeObject; 
    }

    template <typename T> int TypenameOf([[maybe_unused]] std::vector<T> v) const {
        T t;
        return TypeOf(t);
    }

    template <typename T> int TypenameOf([[maybe_unused]] ArrayList<T> v) const {
        T t;
        return TypeOf(t);
    }

    String getName() const;

    int getType() const;

    int getId() const;

    void setName(String);

    void setType(int);

    void setId(int);

    void setReflectObject(_Object * obj);

    // reflect filed set function
    void setValue(int);
    void setValue(long);
    void setValue(uint8_t);
    void setValue(double);
    void setValue(float);
    void setValue(uint16_t);
    void setValue(uint32_t);
    void setValue(uint64_t);
    void setValue(sp<_Object>);
    void setValue(String value);
    void setValue(bool);

    // reflect filed get function
    int getIntValue();
    byte getByteValue();
    double getDoubleValue();
    long getLongValue();
    float getFloatValue();
    uint8_t getUint8Value();
    uint16_t getUint16Value();
    uint32_t getUint32Value();
    uint64_t getUint64Value();
    sp<_Object> getObjectValue();
    String getStringValue();
    bool getBoolValue();

    int getContainerSize();
    sp<_Object> getListItemObject(int);

    // reflect filed create function
    sp<_Object> createObject();
    sp<_Object> createListItemObject();
    void addListItemObject(sp<_Object>);

    // hashmap
    sp<_Pair<sp<_Object>, sp<_Object>>> createMapItemObject();
    sp<_ArrayList<sp<_Pair<sp<_Object>, sp<_Object>>>>>
    getMapItemObjects();
    void addMapItemObject(sp<_Object>, sp<_Object>);

private:
    int type;
    String name;
    int id;
    _Object *object;

    // do not use
    void __setFieldIntValue(const std::string &, int) override {
        // Intentionally unimplemented...
    }
    void __setFieldByteValue(const std::string &, uint8_t) override {
        // Intentionally unimplemented...
    }
    void __setFieldDoubleValue(const std::string &, double) override {
        // Intentionally unimplemented...
    }
    void __setFieldFloatValue(const std::string &, float) override {
        // Intentionally unimplemented...
    }
    void __setFieldUint8Value(const std::string &, uint8_t) override {
        // Intentionally unimplemented...
    }
    void __setFieldUint16Value(const std::string &, uint16_t) override {
        // Intentionally unimplemented...
    }
    void __setFieldUint32Value(const std::string &, uint32_t) override {
        // Intentionally unimplemented...
    }
    void __setFieldUint64Value(const std::string &, uint64_t) override {
        // Intentionally unimplemented...
    }
    void __setFieldObjectValue(const std::string &, sp<_Object>) override {
        // Intentionally unimplemented...
    }
    void __setFieldStringValue([[maybe_unused]] const std::string & name, const std::string value) override {
        // Intentionally unimplemented...
    }
    void __setFieldBoolValue([[maybe_unused]] const std::string & name, bool) override {
        // Intentionally unimplemented...
    }
};

DECLARE_TEMPLATE_CLASS(FieldContent, T) IMPLEMENTS(Field) {
public:
    std::function<void(T)> setfunc;

    explicit _FieldContent(std::function<void(T)> set) { setfunc = set; }
};

DECLARE_CLASS(FieldContentValue) {
public:
    int intValue;
    double doubleValue;
    bool boolValue;
    float floatValue;
    long longValue;
    uint8_t uint8Value;
    uint16_t uint16Value;
    uint32_t uint32Value;
    uint64_t uint64Value;
    String stringValue;
    _Object *objectValue;

    void set(long v) { longValue = v; }

    void set(int v) { intValue = v; }

    void set(double v) { doubleValue = v; }

    void set(bool v) { boolValue = v; }

    void set(float v) { floatValue = v; }

    void set(uint8_t v) { uint8Value = v; }

    void set(uint16_t v) { uint16Value = v; }

    void set(uint32_t v) { uint32Value = v; }

    void set(uint64_t v) { uint64Value = v; }

    void set(String v) { stringValue = v; }

    template <typename T> void set(sp<T> v) {
        objectValue = (_Object *)v.get_pointer();
    }
};

} // namespace obotcha
#endif