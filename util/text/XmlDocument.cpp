#include <iostream>
#include "XmlDocument.hpp"
#include "XmlValue.hpp"

#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;

namespace obotcha {

_XmlDocument::_XmlDocument(long size) {
    mFileSize = size;
}

_XmlDocument::_XmlDocument() {
    mFileSize = 0;
}

XmlValue _XmlDocument::newRootNode(String nodename) {

    rapidxml::xml_node<>* declaration = xmlDoc.allocate_node(rapidxml::node_declaration);
    declaration->append_attribute(xmlDoc.allocate_attribute("version", "1.0"));
    declaration->append_attribute(xmlDoc.allocate_attribute("encoding", "utf-8"));
    xmlDoc.append_node(declaration);

    xml_node<>* rot = xmlDoc.allocate_node(rapidxml::node_element,xmlDoc.allocate_string(nodename->toChars()));
    xmlDoc.append_node(rot);
    XmlValue xmlnode = createXmlValue(rot,this,nodename,nullptr);
    return xmlnode;
}
    
XmlValue _XmlDocument::newNode(String nodename,String value) {
    xml_node<>* node = xmlDoc.allocate_node(node_element,
                                            nodename->toChars(),
                                            value->toChars(),
                                            nodename->size(),
                                            value->size());

    XmlValue xmlnode = createXmlValue(node,this,nodename,value);
    return xmlnode;
}

sp<_XmlAttribute> _XmlDocument::newAttribute(String name,String value) {
    xml_attribute<> *attr = xmlDoc.allocate_attribute(name->toChars(),value->toChars());
    return createXmlAttribute(attr,this,name,value);
}

XmlValue _XmlDocument::getRootNode() {
    xml_node<> *node = xmlDoc.first_node();
    String name = createString(node->name());
    printf("nodeName is %s ,node is %x \n",node->name(),node);
    XmlValue root = createXmlValue(node,this,name,nullptr);
    return root;
}

String _XmlDocument::toString() {
    //std::string text;
    //char buff[1024*256];
    char buff[mFileSize + 1024];
    memset(buff,0,mFileSize + 1024);
    //rapidxml::print(std::back_inserter(text), xmlDoc);
    rapidxml::print(buff, xmlDoc);
    //std::cout<<"to string is "<<text<<std::endl;
    printf("file length is %ld \n",mFileSize);
    return createString(&buff[0]);
}

};
