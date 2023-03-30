#include "XmlReader.hpp"
#include "FileInputStream.hpp"
#include "XmlDocument.hpp"
#include "XmlValue.hpp"

#include "rapidxml_utils.hpp"

namespace obotcha {

_XmlReader::_XmlReader(String content) {
    mDocument = createXmlDocument(content);
}

_XmlReader::_XmlReader(File file) {
    mDocument = createXmlDocument(file);
}

sp<_XmlDocument> _XmlReader::get() { 
    return mDocument; 
}

} // namespace obotcha