#ifndef __OBOTCHA_CONF_WRITER_H__
#define __OBOTCHA_CONF_WRITER_H__

#include "Object.hpp"
#include "File.hpp"
#include "ConfValue.hpp"

namespace obotcha {

DECLARE_CLASS(ConfWriter) {
public:
    explicit _ConfWriter(File f);
    explicit _ConfWriter(String path);
    explicit _ConfWriter(const char *path);

    void write(ConfValue value);

private:
    const static String kConfOutputTemplate;
    File mFile;
};

} // namespace obotcha

#endif