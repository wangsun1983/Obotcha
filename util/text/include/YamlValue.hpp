#ifndef __OBOTCHA_YAML_VALUE_H__
#define __OBOTCHA_YAML_VALUE_H__

#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "yaml-cpp/yaml.h"

namespace obotcha {

class _YamlReader;
class _YamlWriter;

DECLARE_CLASS(YamlValue) {
public:
    friend class _YamlReader;
    friend class _YamlWriter;

    _YamlValue();

    _YamlValue(YAML::Node);

    _YamlValue(YamlValue);

    sp<_YamlValue> getYamlValue(String);

/*
    int getInt(String, int def);

    String getString(String, String def);

    double getDouble(String, double def);

    long getLong(String, long def);

    bool getBool(String, bool def);
 */
    template <typename T>
    T get(String key) {
        return yamlNode[index].as<T>();
    }

    template<typename T = String>
    String get(String key) {
        return createString(yamlNode[index].as<std::string>());
    }

    int getIntAt(int, int def);

    String getStringAt(int, String def);

    double getDoubleAt(int, double def);

    long getLongAt(int, long def);

    bool getBoolAt(int, bool def);

    sp<_YamlValue> getYamlValueAt(int);

    ~_YamlValue();

    int size();

    String getTag();

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
};

} // namespace obotcha

#endif