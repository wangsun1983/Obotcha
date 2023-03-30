#ifndef __OBOTCHA_XML_DOCUMENT_H__
#define __OBOTCHA_XML_DOCUMENT_H__

#include "dictionary.h"
#include "iniparser.h"

#include "ArrayList.hpp"
#include "Field.hpp"
#include "Log.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "StrongPointer.hpp"
#include "XmlValue.hpp"
#include "File.hpp"

#include "OStdInstanceOf.hpp"
#include "TransformException.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

namespace obotcha {

class _XmlValue;
class _XmlAttribute;

DECLARE_CLASS(XmlDocument) {
public:
    friend class _XmlValue;
    friend class _XmlReader;
    friend class _XmlAttribute;

    _XmlDocument(File file);
    _XmlDocument(String content);
    _XmlDocument();
    sp<_XmlValue> newRootNode(String rootNode);
    sp<_XmlValue> newNode(String name, String value);
    sp<_XmlValue> newNode(String name);
    sp<_XmlValue> getRootNode();
    String toString();

    template <typename T> void reflectTo(T value) {
        sp<_XmlValue> root = getRootNode();
        root->reflectTo(value);
    }

    template <typename T> void importFrom(T value) {
        String name = value->__ReflectClassName();
        sp<_XmlValue> root = newRootNode(name);
        root->importFrom(value);
    }

    static const int kDefaultOutputSize;
private:
    xml_document<> xmlDoc;
    rapidxml::file<> fdoc;
    long mContentSize;
};

} // namespace obotcha

#endif