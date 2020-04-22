#include "XmlReader.hpp"
#include "XmlValue.hpp"
#include "XmlDocument.hpp"
#include "FileInputStream.hpp"

#include "rapidxml_utils.hpp"

namespace obotcha {

_XmlReader::_XmlReader(String content) {
    mDocument = createXmlDocument(content);
}

_XmlReader::_XmlReader(File file) {
    xmlfile = file;
    mDocument = createXmlDocument(file->getAbsolutePath(),file->length());
}

sp<_XmlDocument> _XmlReader::get() {
    return mDocument;
}

}