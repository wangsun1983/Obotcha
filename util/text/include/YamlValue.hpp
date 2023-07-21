#ifndef __OBOTCHA_YAML_VALUE_H__
#define __OBOTCHA_YAML_VALUE_H__

#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "yaml-cpp/yaml.h"

namespace obotcha {

class _YamlReader;
class _YamlWriter;
class _YamlValue;

DECLARE_CLASS(YamlValue) {
public:
    friend class _YamlReader;
    friend class _YamlWriter;

    _YamlValue() = default;
    explicit _YamlValue(YAML::Node);

    template <typename T>
    T get(String key);

    template <typename T>
    T getAt(int index);

    void set(String,String);
    void set(String,YamlValue);
    void set(int,String);
    void set(int,YamlValue);
    void set(String);
    void set(YamlValue);

    void pushBack(String);
    void pushBack(YamlValue);

    ~_YamlValue() = default;

    int size();

    String getTag();
    void setTag(String);

    void reflectTo(Object o,int type = ReflectValue);
    void importFrom(Object obj);

private:
    String tag;

    enum ReflectType {
        ReflectName = 0,
        ReflectValue,
    };

    YAML::Node yamlNode;

    void reflectToArrayList(Object obj);
    void reflectToHashMap(Object obj);

    void importArrayListFrom(Object value);
    void importHashMapFrom(Object value);
};

template<typename T>
class _YamlValueHelper {
public:
    explicit _YamlValueHelper(YAML::Node p) {
        node = p;
    }

    T get(String key) {
        return node[key->toChars()].template as<T>();
    }

    T getAt(int index) {
        return node[index].template as<T>();
    }

private:
    YAML::Node node;
};

template<>
class _YamlValueHelper<String> {
public:
    explicit _YamlValueHelper(YAML::Node p) {
        node = p;
    }

    String get(String key) {
        return createString(node[key->toChars()].as<std::string>());
    }

    String getAt(int index) {
        return createString(node[index].as<std::string>());
    }

private:
    YAML::Node node;
};

template<>
class _YamlValueHelper<YamlValue> {
public:
    explicit _YamlValueHelper(YAML::Node p) {
        node = p;
    }

    YamlValue get(String key) {
        YAML::Node newNode = node[key->toChars()].as<YAML::Node>();
        YamlValue result = createYamlValue(newNode);
        result->setTag(createString(node[key->toChars()].Tag()));
        return result;
    }

    YamlValue getAt(int index) {
        YAML::Node newNode = node[index].as<YAML::Node>();
        YamlValue result = createYamlValue(newNode);
        result->setTag(createString(node[index].Tag()));
        return result;
    }

private:
    YAML::Node node;
};

template <typename T>
T _YamlValue::get(String key) {
    return _YamlValueHelper<T>(yamlNode).get(key);
}

template <typename T>
T _YamlValue::getAt(int index) {
    return _YamlValueHelper<T>(yamlNode).getAt(index);
}

} // namespace obotcha

#endif