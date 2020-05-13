#ifndef __OBOTCHA_XML_WRITER_H__
#define __OBOTCHA_XML_WRITER_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

#include "rapidxml.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlValue;
class _XmlDocument;

DECLARE_SIMPLE_CLASS(XmlWriter) {

public:
    friend class _XmlValue;
    friend class _XmlReader;

    _XmlWriter(sp<_XmlDocument> doc);

    void write(String filepath);

private:
    sp<_XmlDocument> xmlDoc;
};

}


#endif