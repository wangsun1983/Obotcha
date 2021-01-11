#include "HttpText.hpp"

namespace obotcha {

const String _HttpText::LineEnd = createString("\r\n");
const String _HttpText::ChunkEnd = createString("\r\n0\r\n");
const String _HttpText::BoundaryTag = createString("boundary");
const String _HttpText::BoundarySeperator = createString("--------------------------");
const String _HttpText::BoundaryBeginning = createString("--");
const String _HttpText::PartName = createString("name");
const String _HttpText::PartFileName = createString("filename");
const String _HttpText::ContentSpace = createString(" ");

}
