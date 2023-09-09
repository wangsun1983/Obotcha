#include "YamlReader.hpp"
#include "InitializeException.hpp"
#include "YamlValue.hpp"

namespace obotcha {

sp<_YamlReader> _YamlReader::loadContent(String content) {
    mValue = createYamlValue();
    mValue->yamlNode = YAML::Load(content->getStdString());
    return AutoClone(this);
}

sp<_YamlReader> _YamlReader::loadFile(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "YamlReader File Error")
    }

    mValue = createYamlValue();
    mValue->yamlNode = YAML::LoadFile(file->getAbsolutePath()->toChars());
    return AutoClone(this);
}

sp<_YamlValue> _YamlReader::parse() { 
    return mValue; 
}

} // namespace obotcha