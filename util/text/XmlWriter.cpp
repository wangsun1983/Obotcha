#include "FileOutputStream.hpp"
#include "Object.hpp"
#include "String.hpp"
#include "XmlDocument.hpp"
#include "XmlValue.hpp"
#include "XmlWriter.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

namespace obotcha {

_XmlWriter::_XmlWriter(sp<_XmlDocument> doc):xmlDoc(doc) {
}

void _XmlWriter::write(String filepath) {
    if (File file = File::New(filepath);!file->exists()) {
        file->createNewFile();
    }

    String content = xmlDoc->toString();
    FileOutputStream stream = FileOutputStream::New(filepath);
    stream->open();
    stream->writeString(content);
    stream->flush();
    stream->close();
}

} // namespace obotcha
