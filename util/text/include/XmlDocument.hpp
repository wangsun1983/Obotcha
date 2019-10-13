#ifndef __XML_DOCUMENT_H__
#define __XML_DOCUMENT_H__

#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlValue;
class _XmlAttribute;

DECLARE_SIMPLE_CLASS(XmlDocument) {

public:
    friend class _XmlValue;
    friend class _XmlReader;
    friend class _XmlAttribute;

    sp<_XmlValue> newRootNode(String rootNode);
    
    sp<_XmlValue> newNode(String name,String value);

    sp<_XmlValue> newNode(String name);

    void load(String);

    void parse();

    //sp<_XmlAttribute> newAttribute(String name,String value);

    sp<_XmlValue> getRootNode();

    String toString();

    _XmlDocument(String path,long size);

    _XmlDocument();

private:
    xml_document<> xmlDoc;

    rapidxml::file<> fdoc;

    long mFileSize;
};

}


#endif