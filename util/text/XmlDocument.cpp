#include <iostream>
#include "XmlDocument.hpp"
#include "XmlValue.hpp"
#include "InitializeException.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

#include "File.hpp"

using namespace rapidxml;

namespace obotcha {

_XmlDocument::_XmlDocument(String path,long size) {
    if(path == nullptr) {
        Trigger(InitializeException,createString("XmlDocument null path!"));
    }

    mFileSize = size;
    
    fdoc = path->toChars();
    this->xmlDoc.parse<0>(fdoc.data());
}

_XmlDocument::_XmlDocument(String content) {
    
    File file = createFile(content);
    mFileSize = file->length();
    fdoc = content->toChars();

    this->xmlDoc.parse<0>(fdoc.data());
}

_XmlDocument::_XmlDocument() {
    mFileSize = 0;
}

XmlValue _XmlDocument::newRootNode(String nodename) {

    rapidxml::xml_node<>* declaration = xmlDoc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8"));
    xmlDoc.append_node(declaration);

    String trimres = nodename->trimAll();

    xml_node<>* rot = xmlDoc.allocate_node(rapidxml::node_element,xmlDoc.allocate_string(trimres->toChars()));
    xmlDoc.append_node(rot);
    XmlValue xmlnode = createXmlValue(rot,this);
    return xmlnode;
}
    
XmlValue _XmlDocument::newNode(String nodename,String value) {
    String trimres = nodename->trimAll();

    xml_node<>* node = xmlDoc.allocate_node(node_element,
                                            xmlDoc.allocate_string(trimres->toChars()),
                                            xmlDoc.allocate_string(value->toChars()),
                                            trimres->size(),
                                            value->size());

    XmlValue xmlnode = createXmlValue(node,this);
    return xmlnode;
}

XmlValue _XmlDocument::newNode(String nodename) {
    String trimres = nodename->trimAll();
    xml_node<>* node = xmlDoc.allocate_node(node_element,
                                            xmlDoc.allocate_string(trimres->toChars()),
                                            nullptr,
                                            trimres->size(),
                                            0);

    XmlValue xmlnode = createXmlValue(node,this);
    return xmlnode;
}

//sp<_XmlAttribute> _XmlDocument::newAttribute(String name,String value) {
//    xml_attribute<> *attr = xmlDoc.allocate_attribute(name->toChars(),value->toChars());
//    return createXmlAttribute(attr,this,name,value);
//}

XmlValue _XmlDocument::getRootNode() {
    xml_node<> *node = xmlDoc.first_node();
    //String name = createString(node->name());
    XmlValue root = createXmlValue(node,this);
    return root;
}

String _XmlDocument::toString() {
    char buff[mFileSize + 1024];
    memset(buff,0,mFileSize + 1024);
    rapidxml::print(buff, xmlDoc);

    return createString(&buff[0]);
}

};
