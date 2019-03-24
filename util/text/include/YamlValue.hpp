#ifndef __YAML_VALUE_H__
#define __YAML_VALUE_H__

#include "yaml-cpp/yaml.h"
#include "StrongPointer.hpp"
#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

class _YamlReader;

DECLARE_SIMPLE_CLASS(YamlValue) {

public:
    friend class _YamlReader;

    _YamlValue();

    _YamlValue(YAML::Node);

    _YamlValue(YamlValue);

    sp<_YamlValue>getYamlValue(String);

    sp<_YamlArray>getYamlArray(String);

    //template<typename T>
    //void reflect(T *t) {
    //    yamlNode >> *t;
    //}
    
    int getInt(String,int def);

    String getString(String,String def);

    double getDouble(String,double def);

    long getLong(String,long def);

    bool getBool(String,bool def);

    ~_YamlValue();

    int size();

private:
    YAML::Node yamlNode;
};

}

#endif