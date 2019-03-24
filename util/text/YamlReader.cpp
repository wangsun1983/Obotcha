#include "YamlReader.hpp"
#include "YamlValue.hpp"
#include "YamlArray.hpp"

namespace obotcha {

 _YamlReader::_YamlReader(const char* path) {
    yamlfile = createFile(path);
 }

_YamlReader::_YamlReader(String path) {
    yamlfile = createFile(path);
}

_YamlReader::_YamlReader(File file) {
    yamlfile = file;
}

sp<_YamlValue> _YamlReader::parseNode() {
    if(yamlfile == nullptr || !yamlfile->exists()) {
        return nullptr;
    }

    YamlValue yaml = createYamlValue();
    yaml->yamlNode = YAML::LoadFile(yamlfile->getAbsolutePath()->toChars());
    return yaml;
}

sp<_YamlArray> _YamlReader::parseArray() {
    if(yamlfile == nullptr || !yamlfile->exists()) {
        return nullptr;
    }

    YamlArray yaml = createYamlArray();
    yaml->yamlNode = YAML::LoadFile(yamlfile->getAbsolutePath()->toChars());
    return yaml;
}

_YamlReader::~_YamlReader() {
    //TOOD
}


}