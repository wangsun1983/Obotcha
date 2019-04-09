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
    String content = xmlDoc->toString();
    printf("xml construct content is %s \n",content->toChars());
}

void _XmlWriter::write(String filepath) {
    String content = xmlDoc->toString();
    FileOutputStream stream = createFileOutputStream(filepath);
    stream->open(st(FileOutputStream)::FileOpenType::Trunc);
    printf("write filepath is %s \n",filepath->toChars());
    printf("write content is %s \n",content->toChars());
    stream->writeString(content);
    stream->flush();
    stream->close();
}

}
