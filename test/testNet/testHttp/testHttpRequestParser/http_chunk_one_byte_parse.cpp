#include "HttpPacketParser.hpp"

using namespace obotcha;

void testChunkOneByteParse() {

  //case 1
  while(1) {
    const char *content = "POST /two_chunks_mult_zero_end HTTP/1.1\r\n"
                 "Transfer-Encoding: chunked\r\n"
                 "\r\n"
                 "5\r\nhello\r\n"
                 "6\r\n world\r\n"
                 "000\r\n"
                 "\r\n";

    HttpPacketParser parser = createHttpPacketParser();
    ArrayList<HttpPacket> packets = createArrayList<HttpPacket>();
    int i = 0;
    for(;i<strlen(content);i++) {
      ByteArray data = createByteArray(1);
      data[0] = (byte)content[i];
      parser->pushHttpData(data);
      packets->add(parser->doParse());
    }

    if(packets->size() != 1) {
      printf("HttpPacketParser chunk message one byte parse case11 [FAILED],packets is %d \n",packets->size());
      break;
    }

    printf("get Content is %s \n",packets->get(0)->getEntity()->getContent()->toString()->toChars());
    break;
  }


  printf("HttpPacketParser chunk message one byte parse case100 [OK] \n");
}
