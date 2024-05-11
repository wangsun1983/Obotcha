#include "XmlDocument.hpp"
#include "InitializeException.hpp"
#include "XmlValue.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include "File.hpp"

namespace obotcha {

const long _XmlDocument::kDefaultOutputSize = 32*1024;

_XmlDocument::_XmlDocument(File file) {
    if (file == nullptr || !file->exists()) {
        Trigger(InitializeException, "XmlDocument null path!")
    }

    mContentSize = file->length();
    fdoc = file->getAbsolutePath()->toChars();
    this->xmlDoc.parse<0>(fdoc.data());
}

_XmlDocument::_XmlDocument(String content) {
    mContentSize = content->size();
    this->xmlDoc.parse<0>(const_cast<char *>(content->toChars()));
}

XmlValue _XmlDocument::newRootNode(String nodename) {
    rapidxml::xml_node<> *declaration =
        xmlDoc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8"));
    xmlDoc.append_node(declaration);

    String trimres = nodename->trimAll();

    rapidxml::xml_node<> *rot = xmlDoc.allocate_node(
        rapidxml::node_element, xmlDoc.allocate_string(trimres->toChars()));
    xmlDoc.append_node(rot);
    return XmlValue::New(rot, this);
}

XmlValue _XmlDocument::newNode(String nodename, String value) {
    String trimres = nodename->trimAll();

    rapidxml::xml_node<> *node = xmlDoc.allocate_node(
        rapidxml::node_element, xmlDoc.allocate_string(trimres->toChars()),
        xmlDoc.allocate_string(value->toChars()), trimres->size(),
        value->size());

    return XmlValue::New(node, this);
}

XmlValue _XmlDocument::newNode(String nodename) {
    String trimres = nodename->trimAll();
    rapidxml::xml_node<> *node = xmlDoc.allocate_node(
        rapidxml::node_element, xmlDoc.allocate_string(trimres->toChars()), nullptr,
        trimres->size(), 0);

    return XmlValue::New(node, this);
}

XmlValue _XmlDocument::getRootNode() {
    rapidxml::xml_node<> *node = xmlDoc.first_node();
    return XmlValue::New(node, this);
}

String _XmlDocument::toString() {
    long len = (mContentSize == 0)? kDefaultOutputSize:mContentSize;
    char buff[len];
    memset(buff,0,len);
    rapidxml::print(buff, xmlDoc);
    return String::New(&buff[0]);
}

}; // namespace obotcha
