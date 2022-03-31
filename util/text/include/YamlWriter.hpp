#ifndef __OBOTCHA_YAML_WRITER_H__
#define __OBOTCHA_YAML_WRITER_H__

#include "File.hpp"
#include "String.hpp"
#include "YamlValue.hpp"

namespace obotcha {

DECLARE_CLASS(YamlWriter) {
public:
    _YamlWriter(String path);

    _YamlWriter(File);

    void write(YamlValue);

private:
    File mFile;
};

} // namespace obotcha

#endif