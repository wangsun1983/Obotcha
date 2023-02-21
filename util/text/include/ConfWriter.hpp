#ifndef __OBOTCHA_CONF_WRITER_H__
#define __OBOTCHA_CONF_WRITER_H__

#include "File.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "ConfValue.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

DECLARE_CLASS(ConfWriter) {
public:
    _ConfWriter(File f);
    _ConfWriter(String path);
    _ConfWriter(const char *);

    void write(ConfValue value);

    void close();

    const static String ConfOutputTemplate;
private:
    File mFile;
};

} // namespace obotcha

#endif