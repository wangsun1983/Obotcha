#ifndef __OBOTCHA_XML_READER_H__
#define __OBOTCHA_XML_READER_H__

#include "File.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "XmlValue.hpp"
#include "rapidxml.hpp"

namespace obotcha {

class _XmlDocument;

DECLARE_CLASS(XmlReader) {
public:
    // explicit _XmlReader(String content);

    // explicit _XmlReader(File file);
    explicit _XmlReader() = default;
    sp<_XmlReader> loadContent(String);    
    sp<_XmlReader> loadFile(File);

    sp<_XmlDocument> get();
private:
    File xmlfile;

    sp<_XmlDocument> mDocument;
};

} // namespace obotcha

#endif