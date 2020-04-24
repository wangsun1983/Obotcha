#include "YamlReader.hpp"
#include "YamlValue.hpp"
#include "YamlArray.hpp"

namespace obotcha {

 _YamlValue::_YamlValue() {
    //TODO
 }

_YamlValue::_YamlValue(YAML::Node v) {
    yamlNode = v;
}

sp<_YamlValue> _YamlValue::getYamlValue(String tag) {
    if(tag == nullptr) {
        return nullptr;
    }

    try {
        const char *name = tag->toChars();
        YAML::Node newNode = yamlNode[name].as<YAML::Node>();

        YamlValue result = createYamlValue(newNode);
        return result;

    } catch (std::exception &e) {
        return nullptr;
    }

    return nullptr;
}
    
int _YamlValue::getInt(String tag,int def) {
    if(tag == nullptr) {
        return def;
    }

    try {
        const char *name = tag->toChars();
        int result = yamlNode[name].as<int>();
        return result;

    } catch (std::exception &e) {
        return def;
    }

    return def;
}

String _YamlValue::getString(String tag,String def) {
    if(tag == nullptr) {
        return def;
    }

    try {
        const char *name = tag->toChars();
        std::string result = yamlNode[name].as<std::string>();
        return createString(result);

    } catch (std::exception &e) {
        return def;
    }

    return def;
}

double _YamlValue::getDouble(String tag,double def) {
    if(tag == nullptr) {
        return def;
    }

    try {
        const char *name = tag->toChars();
        double result = yamlNode[name].as<double>();
        return result;
    } catch (std::exception &e) {
        return def;
    }

    return def;
}

long _YamlValue::getLong(String tag,long def) {
    if(tag == nullptr) {
        return def;
    }

    try {
        const char *name = tag->toChars();
        long result = yamlNode[name].as<long>();
        return result;
    } catch (std::exception &e) {
        return def;
    }

    return def;
}

bool _YamlValue::getBool(String tag,bool def) {
    if(tag == nullptr) {
        return def;
    }

    try {
        const char *name = tag->toChars();
        bool result = yamlNode[name].as<bool>();
        return result;
    } catch (std::exception &e) {
        return def;
    }

    return def;
}

int _YamlValue::getIntAt(int index,int def) {
    try {
        int result = yamlNode[index].as<int>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

String _YamlValue::getStringAt(int index,String def) {
    try {
        std::string result = yamlNode[index].as<std::string>();
        return createString(result);

    } catch (std::exception &e) {
        return def;
    }
}

double _YamlValue::getDoubleAt(int index,double def) {
    try {
        double result = yamlNode[index].as<double>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

long _YamlValue::getLongAt(int index,long def) {
    try {
        long result = yamlNode[index].as<long>();
        return result;
    } catch (std::exception &e) {
        return def;
    }
}

bool _YamlValue::getBoolAt(int index,bool def) {
    try {
        bool result = yamlNode[index].as<bool>();
        return result;
    } catch (std::exception &e) {
        return def;
    } 
}

sp<_YamlValue> _YamlValue::getYamlValueAt(int index) {
    try {
        YAML::Node newNode = yamlNode[index].as<YAML::Node>();

        YamlValue result = createYamlValue(newNode);
        return result;

    } catch (std::exception &e) {
        return nullptr;
    }
}

int _YamlValue::size() {
    return yamlNode.size();
}

_YamlValue::~_YamlValue() {

}


}