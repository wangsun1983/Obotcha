#ifndef __OBOTCHA_XML_READER_H__
#define __OBOTCHA_XML_READER_H__

#include "File.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "XmlValue.hpp"
#include "rapidxml.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlDocument;

DECLARE_CLASS(XmlReader) {
public:
    _XmlReader(String content);

    _XmlReader(File file);

    sp<_XmlDocument> get();

private:
    File xmlfile;

    sp<_XmlDocument> mDocument;
};

} // namespace obotcha

#endif