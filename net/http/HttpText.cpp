#include "HttpText.hpp"

namespace obotcha {

// const String _HttpText::LineEnd = createString("\r\n");
// const String _HttpText::DoubleLineEnd = createString("\r\n\r\n");
const String _HttpText::HttpEnd = createString("\r\n\r\n");
const String _HttpText::Boundary = createString("boundary");
//const String _HttpText::BoundarySeperator = createString("-----------------------------");
const String _HttpText::BoundaryBeginning = createString("--");
const String _HttpText::MultiPartFileName = createString("filename");
const String _HttpText::MultiPartName = createString("name");
const String _HttpText::MultiPartEnd = createString("--\r\n");
const String _HttpText::CRLF = createString("\r\n");
const String _HttpText::CR = createString("\r");
const String _HttpText::LF = createString("\n");

// const String _HttpText::PartName = createString("name");
// const String _HttpText::PartFileName = createString("filename");
const String _HttpText::ContentSpace = createString(" ");
const String _HttpText::ContentHttp = createString("HTTP");

} // namespace obotcha
