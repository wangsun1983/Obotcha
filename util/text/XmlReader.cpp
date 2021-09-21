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
    xmlfile = file;
    mDocument = createXmlDocument(file->getAbsolutePath(), file->length());
}

sp<_XmlDocument> _XmlReader::get() { return mDocument; }

} // namespace obotcha