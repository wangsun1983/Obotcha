#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"
#include "FileInputStream.hpp"

#include "rapidxml_utils.hpp"

namespace obotcha {

_XmlReader::_XmlReader(const char* path) {
    xmlfile = createFile(path);
    //xmlfile->setPath(createString(path));
}

_XmlReader::_XmlReader(String path) {
    xmlfile = createFile(path);
}

_XmlReader::_XmlReader(File file) {
    xmlfile = file;
}

sp<_XmlDocument> _XmlReader::parse() {
    String path = xmlfile->getAbsolutePath();
    if(path != nullptr) {

        XmlDocument document = createXmlDocument(path,xmlfile->length());
        document->parse();
        
        //xml_node<> *node = document->xmlDoc.first_node();
        return document;
    }
    
    return nullptr;
}

}