#ifndef __OBOTCHA_XML_DOCUMENT_H__
#define __OBOTCHA_XML_DOCUMENT_H__

#include "Log.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "XmlValue.hpp"
#include "File.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

namespace obotcha {

class _XmlAttribute;

DECLARE_CLASS(XmlDocument) {
public:
    friend class _XmlValue;
    friend class _XmlReader;
    friend class _XmlAttribute;

    _XmlDocument() = default;
    explicit _XmlDocument(File file);
    explicit _XmlDocument(String content);

    XmlValue newRootNode(String rootNode);
    XmlValue newNode(String name, String value);
    XmlValue newNode(String name);
    XmlValue getRootNode();
    String toString() override;

    template <typename T> void reflectTo(T value) {
        XmlValue root = getRootNode();
        root->reflectTo(value);
    }

    template <typename T> void importFrom(T value) {
        String name = value->__ReflectClassName();
        XmlValue root = newRootNode(name);
        root->importFrom(value);
    }

    static const long kDefaultOutputSize;
private:
    rapidxml::xml_document<> xmlDoc;
    rapidxml::file<> fdoc;
    long mContentSize = 0;
};

} // namespace obotcha

#endif