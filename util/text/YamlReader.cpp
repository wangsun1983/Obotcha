#include "YamlReader.hpp"
#include "YamlValue.hpp"
#include "YamlArray.hpp"
#include "InitializeException.hpp"

namespace obotcha {

_YamlReader::_YamlReader(String content) {
    mValue = createYamlValue();
    mValue->yamlNode = YAML::Load(content->getStdString());
}

_YamlReader::_YamlReader(File file) {
    if(file == nullptr || !file->exists()) {
        throw InitializeException("YamlReader File Error");
    }
    
    mValue = createYamlValue();
    mValue->yamlNode = YAML::LoadFile(file->getAbsolutePath()->toChars());
}

sp<_YamlValue> _YamlReader::get() {
    return mValue;
}

_YamlReader::~_YamlReader() {
    //TOOD
}


}