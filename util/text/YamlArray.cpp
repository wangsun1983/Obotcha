#include "YamlArray.hpp"
#include "YamlValue.hpp"

namespace obotcha {

_YamlArray::_YamlArray() {

}

_YamlArray::_YamlArray(YAML::Node v) {
    yamlNode = v;
}

_YamlArray::_YamlArray(YamlArray v) {
    yamlNode = v->yamlNode;
}

sp<_YamlValue> _YamlArray::getYamlValue(int index) {
    if(index >= yamlNode.size()) {
        return nullptr;
    }

    YAML::Node node = yamlNode;
    return createYamlValue(node);
}

int _YamlArray::size() {
    return yamlNode.size();
}

int _YamlArray::getInt(int index,int def) {
    if(index >= yamlNode.size()) {
        return def;
    }

    return yamlNode[index].as<int>();
}

String _YamlArray::getString(int index,String def) {
    if(index >= yamlNode.size()) {
        return def;
    }

    std::string str = yamlNode[index].as<std::string>();

    return createString(str);
}

double _YamlArray::getDouble(int index,double def) {
    if(index >= yamlNode.size()) {
        return def;
    }

    return yamlNode[index].as<double>();
}

long _YamlArray::getLong(int index,long def) {
    if(index >= yamlNode.size()) {
        return def;
    }

    return yamlNode[index].as<long>();
}

bool _YamlArray::getBool(int index,bool def){
    if(index >= yamlNode.size()) {
        return def;
    }

    return yamlNode[index].as<bool>();
}

}