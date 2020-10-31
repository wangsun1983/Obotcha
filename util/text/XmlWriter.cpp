#include "iniparser.h"
#include "dictionary.h"

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "FileOutputStream.hpp"
#include "XmlWriter.hpp"
#include "XmlDocument.hpp"
#include "XmlValue.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"

using namespace rapidxml;

namespace obotcha {

_XmlWriter::_XmlWriter(sp<_XmlDocument> doc) {
    xmlDoc = doc;
}

void _XmlWriter::write(String filepath) {
    File file = createFile(filepath);
    if(!file->exists()) {
        file->createNewFile();
    }

    String content = xmlDoc->toString();
    FileOutputStream stream = createFileOutputStream(filepath);
    stream->open(st(OutputStream)::Trunc);
    stream->writeString(content);
    stream->flush();
    stream->close();
}

}
