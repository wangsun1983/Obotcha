#ifndef __OBOTCHA_YAML_READER_H__
#define __OBOTCHA_YAML_READER_H__

#include "File.hpp"
#include "String.hpp"

namespace obotcha {
class _YamlValue;
class _YamlArray;

DECLARE_CLASS(YamlReader) {
public:
    explicit _YamlReader() = default;
    sp<_YamlReader> loadContent(String);
    
    sp<_YamlReader> loadFile(File);

    
    ~_YamlReader() override = default;

    sp<_YamlValue> parse();

private:
    sp<_YamlValue> mValue;
};

} // namespace obotcha

#endif