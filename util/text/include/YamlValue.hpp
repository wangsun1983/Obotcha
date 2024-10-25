#ifndef __OBOTCHA_YAML_VALUE_H__
#define __OBOTCHA_YAML_VALUE_H__

#include "yaml-cpp/yaml.h"

#include "Object.hpp"
#include "String.hpp"
#include "Text.hpp"

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

    ~_YamlValue() override = default;

    size_t size() const;
    String getTag() const;
    void setTag(String);

    void reflectTo(Object o,st(Text)::Syntax type = st(Text)::Syntax::Value);
    void importFrom(Object obj);

private:
    String tag;

    YAML::Node yamlNode;

    void reflectToArrayList(Object obj);
    void reflectToHashMap(Object obj);
    void importArrayListFrom(Object value);
    void importHashMapFrom(Object value);
};

template<typename T>
class _YamlValueHelper {
public:
    explicit _YamlValueHelper(const YAML::Node &p):node(p) {
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
    explicit _YamlValueHelper(const YAML::Node &p):node(p) {
    }

    String get(String key) {
        return String::New(node[key->toChars()].as<std::string>());
    }

    String getAt(int index) {
        return String::New(node[index].as<std::string>());
    }

private:
    YAML::Node node;
};

template<>
class _YamlValueHelper<YamlValue> {
public:
    explicit _YamlValueHelper(const YAML::Node &p):node(p) {
    }

    YamlValue get(String key) {
        YAML::Node newNode = node[key->toChars()].as<YAML::Node>();
        YamlValue result = YamlValue::New(newNode);
        result->setTag(String::New(node[key->toChars()].Tag()));
        return result;
    }

    YamlValue getAt(int index) {
        YAML::Node newNode = node[index].as<YAML::Node>();
        YamlValue result = YamlValue::New(newNode);
        result->setTag(String::New(node[index].Tag()));
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