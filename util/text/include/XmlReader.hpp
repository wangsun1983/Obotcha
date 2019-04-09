#ifndef __XML_READER_H__
#define __XML_READER_H__

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
    _XmlReader(const char* path);

    _XmlReader(String path);

    _XmlReader(File file);

    sp<_XmlDocument> parse();

private:
    File xmlfile;

    //sp<_XmlDocument> doc;
};

}

#endif