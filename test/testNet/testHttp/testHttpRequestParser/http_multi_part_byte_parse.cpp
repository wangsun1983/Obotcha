#include "HttpPacketParser.hpp"

using namespace obotcha;

void testMultiPartOneByteParse() {

  //case 1
  while(1) {
    const char *content =
        "POST /handset/save HTTP/1.1\r\n"
        "Host: gateway.ereneben.com\r\n"
        "Accept: */*\r\n"
        "User-Agent: T1 HTTP Adaptor\r\n"
        "Connection: Keep-Alive\r\n"
        "User-Serial: 1234567890ABCDEFGHIJKLMC\r\n"
        "User-Cert: Q+XuG7315JEIzRw9atIvjhCv0d8+4CN5ZGLZWBPs+1FjUcl5Bijd859rG4BUbIJrjoK2dbEuMMC8XmFAcuxJ2SSyXMty63iu0tnhsCJhgPmo4bFV0Px+V9CwKLixNa/+7bX2t3sCz7TMPfrYlKECF3xm4rB9q9/6htFKxCv99q4="
        "\r\n"
        "User-ID: 122\r\n"
        "Content-Type: multipart/form-data; boundary=--------------------------7d93b91e2404d\r\n"
        "Content-Length: 299\r\n"
        "\r\n"
        "----------------------------7d93b91e2404d\r\n"
        "Content-Disposition: form-data; name=\"update1\"; filename=\"/Storage Card/eben.txt\"\r\n"
        "Content-Type: application/octet-stream; charset=GBK\r\n"
        "Transfer-Encoding: binary\r\n"
        "\r\n"
        "CkAtom C++ Class Reference (Visual C++)"
        "\r\n"
        "----------------------------7d93b91e2404d--"
        "\r\n";

    HttpPacketParser parser = createHttpPacketParser();
    //parser->pushHttpData(createByteArray((const byte *)content,strlen(content)));
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    int i = 0;
    for(;i<strlen(content);i++) {
      ByteArray data = createByteArray(1);
      data[0] = (byte)content[i];
      parser->pushHttpData(data);
      ArrayList<HttpPacket> r = parser->doParse();
      if(r != nullptr && r->size() != 0) {
        packets->add(r);
      }
    }

    if(packets->size() != 1) {
      printf("HttpPacketParser chunk message one byte parse case11 [FAILED],packets is %d \n",packets->size());
      break;
    }

    break;
  }


  printf("HttpPacketParser chunk message one byte parse case100 [OK] \n");
}
