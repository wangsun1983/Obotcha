#include "XmlReader.hpp"

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

XmlValue _XmlReader::parse() {
    String path = xmlfile->getAbsolutePath();
    if(path != nullptr) {
        doc.parse<0>(const_cast<char *>(path->toChars()));
    }
    
    return nullptr;
}

}