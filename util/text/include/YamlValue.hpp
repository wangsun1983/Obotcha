#ifndef __OBOTCHA_YAML_VALUE_H__
#define __OBOTCHA_YAML_VALUE_H__

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

    int getInt(String,int def);

    String getString(String,String def);

    double getDouble(String,double def);

    long getLong(String,long def);

    bool getBool(String,bool def);

    int getIntAt(int,int def);

    String getStringAt(int,String def);

    double getDoubleAt(int,double def);

    long getLongAt(int,long def);

    bool getBoolAt(int,bool def);

    sp<_YamlValue> getYamlValueAt(int);
  
    ~_YamlValue();

    int size();

private:
    YAML::Node yamlNode;
};

}

#endif