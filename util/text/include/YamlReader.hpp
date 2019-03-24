#ifndef __YAML_READER_H__
#define __YAML_READER_H__

#include "File.hpp"
#include "String.hpp"

namespace obotcha {
class _YamlValue;
class _YamlArray;

DECLARE_SIMPLE_CLASS(YamlReader) {

public:
    _YamlReader(const char* path);

    _YamlReader(String path);

    _YamlReader(File file);

    sp<_YamlValue> parseNode();

    sp<_YamlArray> parseArray();

    ~_YamlReader();

private:
    File yamlfile;
};

}

#endif