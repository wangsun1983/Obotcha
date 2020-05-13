#ifndef __OBOTCHA_YAML_ARRAY_H__
#define __OBOTCHA_YAML_ARRAY_H__

#include "yaml-cpp/yaml.h"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class _YamlReader;
class _YamlValue;

DECLARE_SIMPLE_CLASS(YamlArray) {

public:
    friend class _YamlReader;

    _YamlArray();

    _YamlArray(YAML::Node);

    _YamlArray(YamlArray);

    sp<_YamlValue>getYamlValue(int index);

    int getInt(int index,int def);

    String getString(int index,String def);

    double getDouble(int index,double def);

    long getLong(int index,long def);

    bool getBool(int index,bool def);

    int size();

private:
    YAML::Node yamlNode;
};

}

#endif