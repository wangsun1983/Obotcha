#ifndef __OBOTCHA_YAML_READER_H__
#define __OBOTCHA_YAML_READER_H__

#include "File.hpp"
#include "String.hpp"

namespace obotcha {
class _YamlValue;
class _YamlArray;

DECLARE_SIMPLE_CLASS(YamlReader) {

public:

    _YamlReader(String content);

    _YamlReader(File file);

    ~_YamlReader();

    sp<_YamlValue> get();

private:
    sp<_YamlValue> mValue;

};

}

#endif