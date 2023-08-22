#ifndef __OBOTCHA_YAML_WRITER_H__
#define __OBOTCHA_YAML_WRITER_H__

#include "File.hpp"
#include "String.hpp"
#include "YamlValue.hpp"

namespace obotcha {

DECLARE_CLASS(YamlWriter) {
public:
    explicit _YamlWriter(String path);

    explicit _YamlWriter(File);

    void write(YamlValue) const;

private:
    File mFile;
};

} // namespace obotcha

#endif