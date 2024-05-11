#include "HttpText.hpp"

namespace obotcha {

const String _HttpText::HttpEnd           =   String::New("\r\n\r\n");
const String _HttpText::Boundary          =   String::New("boundary");
const String _HttpText::BoundaryBeginning =   String::New("--");
const String _HttpText::MultiPartFileName =   String::New("filename");
const String _HttpText::MultiPartName     =   String::New("name");
const String _HttpText::MultiPartEnd      =   String::New("--\r\n");
const String _HttpText::CRLF              =   String::New("\r\n");
const String _HttpText::CR                =   String::New("\r");
const String _HttpText::LF                =   String::New("\n");
const String _HttpText::ContentSpace      =   String::New(" ");
const String _HttpText::ContentHttp       =   String::New("HTTP");
const String _HttpText::HttpChunkEnd      =   String::New("0\r\n\r\n");
const String _HttpText::MultiPartFileTemplate = String::New("--%s\r\ncontent-disposition: form-data; name=\"%s\"; filename=\"%s\"\r\nContent-Type: %s\r\n\r\n");
const String _HttpText::MultiPartContentTemplate = String::New("--%s\r\ncontent-disposition: form-data; name=\"%s\"\r\n\r\n%s\r\n");
const String _HttpText::MultiPartEndTemplate = String::New("--%s--\r\n");

} // namespace obotcha
