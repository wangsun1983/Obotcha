#include "XmlReader.hpp"
#include "FileInputStream.hpp"
#include "XmlDocument.hpp"
#include "XmlValue.hpp"

#include "rapidxml_utils.hpp"

namespace obotcha {

sp<_XmlReader> _XmlReader::loadContent(String content) {
    mDocument = createXmlDocument(content);
    return AutoClone(this);
}

sp<_XmlReader> _XmlReader::loadFile(File file) {
    mDocument = createXmlDocument(file);
    return AutoClone(this);
}

sp<_XmlDocument> _XmlReader::get() { 
    return mDocument; 
}

} // namespace obotcha