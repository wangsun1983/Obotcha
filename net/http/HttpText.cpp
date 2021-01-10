#include "HttpText.hpp"

namespace obotcha {

String _HttpText::LineEnd = createString("\r\n");
String _HttpText::BoundaryTag = createString("boundary");
String _HttpText::BoundarySeperator = createString("--------------------------");
String _HttpText::BoundaryBeginning = createString("--");
String _HttpText::PartName = createString("name");
String _HttpText::PartFileName = createString("filename");

}
