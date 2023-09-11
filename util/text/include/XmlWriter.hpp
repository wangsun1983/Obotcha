#ifndef __OBOTCHA_XML_WRITER_H__
#define __OBOTCHA_XML_WRITER_H__

#include "Object.hpp"
#include "String.hpp"

#include "rapidxml.hpp"

namespace obotcha {

class _XmlValue;
class _XmlDocument;

DECLARE_CLASS(XmlWriter) {
public:
    friend class _XmlValue;
    friend class _XmlReader;

    explicit _XmlWriter(sp<_XmlDocument> doc);

    void write(String filepath);

private:
    sp<_XmlDocument> xmlDoc;
};

} // namespace obotcha

#endif