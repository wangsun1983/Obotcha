#include "YamlReader.hpp"
#include "InitializeException.hpp"
#include "YamlValue.hpp"

namespace obotcha {

_YamlReader::_YamlReader(String content) {
    mValue = createYamlValue();
    mValue->yamlNode = YAML::Load(content->getStdString());
}

_YamlReader::_YamlReader(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "YamlReader File Error");
    }

    mValue = createYamlValue();
    mValue->yamlNode = YAML::LoadFile(file->getAbsolutePath()->toChars());
}

sp<_YamlValue> _YamlReader::parse() { 
    return mValue; 
}

} // namespace obotcha