#ifndef __OBOTCHA_XML_READER_H__
#define __OBOTCHA_XML_READER_H__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "IniValue.hpp"
#include "File.hpp"
#include "rapidxml.hpp"
#include "XmlValue.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlDocument;

DECLARE_SIMPLE_CLASS(XmlReader) {

public:
    _XmlReader(String content);

    _XmlReader(File file);

    sp<_XmlDocument> get();

private:
    File xmlfile;

    sp<_XmlDocument> mDocument;
};

}

#endif