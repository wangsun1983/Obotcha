#include "HttpPacketParser.hpp"

using namespace obotcha;

void testMultiMessageParse() {

  //case1
  while(1) {
    const char *content = "GET /test HTTP/1.1\r\n"
                 "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
                 "Host: 0.0.0.0=5000\r\n"
                 "Accept: */*\r\n"
                 "\r\n"
                 "GET /test HTTP/1.1\r\n"
                "User-Agent: curl/7.18.0 (i486-pc-linux-gnu) libcurl/7.18.0 OpenSSL/0.9.8g zlib/1.2.3.3 libidn/1.1\r\n"
                "Host: 0.0.0.0=5000\r\n"
                "Accept: */*\r\n"
                "\r\n";

    HttpPacketParser parser = createHttpPacketParser();

    parser->pushHttpData(createByteArray((const byte *)content,strlen(content)));
    ArrayList<HttpPacket> packets = parser->doParse();
    if(packets->size() != 2) {
      printf("HttpPacketParser multi message parse case1 [FAILED] \n");
    }
    break;
  }

  //case2
  while(1) {
    const char *content = "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO"
                 "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                              "conTENT-Length: 5\r\n"
                              "\r\n"
                              "WORLD";

    HttpPacketParser parser = createHttpPacketParser();

    parser->pushHttpData(createByteArray((const byte *)content,strlen(content)));
    ArrayList<HttpPacket> packets = parser->doParse();
    if(packets->size() != 2) {
      printf("HttpPacketParser multi message parse case2 [FAILED] \n");
      break;
    }

    auto pac0 = packets->get(0);
    if(!pac0->getEntity()->getContent()->toString()->equals("HELLO")) {
      printf("HttpPacketParser multi message parse case3 [FAILED] \n");
      break;
    }

    auto pac1 = packets->get(1);
    if(!pac1->getEntity()->getContent()->toString()->equals("WORLD")) {
      printf("HttpPacketParser multi message parse case4 [FAILED] \n");
      break;
    }

    break;
  }

  //case3
  while(1) {
    const char *content = "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO"
                 "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                              "conTENT-Length: 5\r\n";


    HttpPacketParser parser = createHttpPacketParser();

    parser->pushHttpData(createByteArray((const byte *)content,strlen(content)));
    ArrayList<HttpPacket> packets = parser->doParse();
    if(packets->size() != 1) {
      printf("HttpPacketParser multi message parse case3 [FAILED] \n");
      break;
    }

    auto pac0 = packets->get(0);
    if(!pac0->getEntity()->getContent()->toString()->equals("HELLO")) {
      printf("HttpPacketParser multi message parse case4 [FAILED] \n");
      break;
    }

    const char* content2 = "\r\n"
                            "WORLD";
    parser->pushHttpData(createByteArray((const byte *)content2,strlen(content2)));
    packets = parser->doParse();
    if(packets->size() != 1) {
      printf("HttpPacketParser multi message parse case5 [FAILED] \n");
      break;
    }

    auto pac1 = packets->get(0);
    if(!pac1->getEntity()->getContent()->toString()->equals("WORLD")) {
      printf("HttpPacketParser multi message parse case6 [FAILED] \n");
      break;
    }

    break;
  }

  //case4
  while(1) {
    const char *content = "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO";
    HttpPacketParser parser = createHttpPacketParser();
    ArrayList<HttpPacket> packets;
    int i = 0;

    for(;i<strlen(content);i++) {
      ByteArray data = createByteArray(1);
      data[0] = (byte)content[i];
      parser->pushHttpData(data);
      packets = parser->doParse();
    }

    if(i != strlen(content)) {
      printf("HttpPacketParser multi message parse case7 [FAILED],i is %d,strlen(content) is %d \n",i,strlen(content));
      break;
    }

    auto pac1 = packets->get(0);
    if(!pac1->getEntity()->getContent()->toString()->equals("HELLO")) {
      printf("HttpPacketParser multi message parse case8 [FAILED] \n");
      break;
    }
    break;
  }

  //case5
  while(1) {
    const char *content = "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                 "conTENT-Length: 5\r\n"
                 "\r\n"
                 "HELLO"
                 "GET /get_funky_content_length_body_hello HTTP/1.0\r\n"
                              "conTENT-Length: 5\r\n"
                              "\r\n"
                              "WORLD";

    HttpPacketParser parser = createHttpPacketParser();
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    int i = 0;

    for(;i<strlen(content);i++) {
      ByteArray data = createByteArray(1);
      data[0] = (byte)content[i];
      parser->pushHttpData(data);
      auto ret = parser->doParse();
      packets->add(ret);
    }

    if(i != strlen(content)) {
      printf("HttpPacketParser multi message parse case9 [FAILED],i is %d,strlen(content) is %d \n",i,strlen(content));
      break;
    }

    auto pac1 = packets->get(0);
    if(!pac1->getEntity()->getContent()->toString()->equals("HELLO")) {
      printf("HttpPacketParser multi message parse case10 [FAILED] \n");
      break;
    }

    auto pac2 = packets->get(1);
    if(!pac2->getEntity()->getContent()->toString()->equals("WORLD")) {
      printf("HttpPacketParser multi message parse case11 [FAILED] \n");
      break;
    }
    break;
  }

  printf("HttpPacketParser multi message parse case100 [OK] \n");
}
