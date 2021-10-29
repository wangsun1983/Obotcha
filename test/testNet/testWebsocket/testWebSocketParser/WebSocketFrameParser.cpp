#include <stdio.h>
#include <unistd.h>

#include "Integer.hpp"
#include "StrongPointer.hpp"
#include "Long.hpp"
#include "WebSocketServer.hpp"
#include "WebSocketListener.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "AutoLock.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"
#include "WebSocketHybi13Parser.hpp"

using namespace obotcha;

static inline char *mask(char key[4], char *payload, size_t length) {
    size_t i, j;
    for (i = 0, j = 0; i < length; i++, j++){
        payload[i] = payload[i] ^ key[j % 4];
    }
    return payload;
}

static inline uint64_t htons64(uint64_t value) {
	static const int num = 42;

	/**
	 * If this check is true, the system is using the little endian
	 * convention. Else the system is using the big endian convention, which
	 * means that we do not have to represent our integers in another way.
	 */
	if (*(char *)&num == 42) {
        return ((uint64_t)htonl((value) & 0xFFFFFFFFLL) << 32) | htonl((value) >> 32);
	} else {
        return value;
	}
}

static void *WSS_copy(void *ptr, size_t size) {
        void *buffer;

    if (ptr == NULL) {
        return NULL;
    }

    if (NULL == (buffer = malloc(size)) ) {
        return NULL;
    }

    return memcpy(buffer, ptr, size);
}


int testFrameParser() {
  //case 1
  {
    //0x88 0x80 0xb3 0x24 0xb2 0x4e
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";
    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload,strlen(payload));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() == 0) {
      printf("testFrameParser case1 size check failed,it is 0 \n");
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case1 frame check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case1 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
    }
  }

  //case 1_1
  {
    //0x88 0x80 0xb3 0x24 0xb2 0x4e
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58"
                          "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";

    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload,strlen(payload));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() != 2) {
      printf("testFrameParser case1_1 size check failed,it is 0 \n");
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case1_2 frame check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case1_3 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
    }

    WebSocketFrame frame1 = msgDatas->get(1);
    if(frame1->getData() == nullptr) {
      printf("testFrameParser case1_4 frame check failed frame is null \n");
      return -1;
    }

    if(!frame1->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case1_5 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
    }
  }


  //case2
  {
    //0x88 0x80 0xb3 0x24 0xb2 0x4e
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";
    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload,strlen(payload));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() != 2) {
      printf("testFrameParser case2 size is error,now is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case2 frame1 check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case2 frame1 check failed frame is %s \n",frame->getData()->toString()->toChars());
    }

    frame = msgDatas->get(1);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case2 frame2 check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case2 frame2 check failed frame is %s \n",frame->getData()->toString()->toChars());
      return -1;
    }
  }

  //case 3
  {
      size_t offset = 0;
      const char *header = "\x81\xFE";
      const char *key = "\x37\xfa\x21\x3d";
      const char *payload = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin hendrerit ornare tortor ut euismod. Nunc finibus convallis sem, at imperdiet ligula commodo id. Nam bibendum nec augue in posuere mauris.";
      uint16_t length = strlen(payload);
      char *payload_copy = (char *)WSS_copy((void *)payload, length);
      char payload_frame[(2+2+4+length)*sizeof(char)];
      uint16_t len = htons(length);
      memcpy(payload_frame, header, 2);
      memcpy(payload_frame+2, &len, 2);
      memcpy(payload_frame+2+2, key, 4);
      memcpy(payload_frame+2+2+4, (const char *)mask((char *)key, payload_copy, length), length);

      WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
      ByteArray loadData = createByteArray((const byte *)payload_frame,(2+2+4+length));
      parser->pushParseData(loadData);
      ArrayList<WebSocketFrame> msgDatas = parser->doParse();
      if(msgDatas->size() != 1) {
        printf("testFrameParser case3 size is error,now is %d \n",msgDatas->size());
        return -1;
      }

      WebSocketFrame frame = msgDatas->get(0);
      if(frame->getData() == nullptr) {
        printf("testFrameParser case3 frame check failed frame is null \n");
        return -1;
      }

      if(!frame->getData()->toString()->equals(payload)) {
        printf("testFrameParser case3 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
        return -1;
      }
      free(payload_copy);
  }

  //case4
  {
    size_t offset = 0;
    const char *header = "\x81\xFF";
    const char *key = "\x37\xfa\x21\x3d";
    const char *p = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin hendrerit ornare tortor ut euismod. Nunc finibus convallis sem, at imperdiet ligula commodo id. Nam bibendum nec augue in posuere mauris.";
    char payload[66001];
    memset(payload,0,66001);

    size_t plen = strlen(p);
    size_t poff = 0;
    while(poff != 66000) {
        memcpy(payload+poff, p, plen);
        poff+=plen;
    }

    uint64_t length = strlen(payload);
    char *payload_copy = (char *)WSS_copy((void *)payload, length);
    char payload_frame[(2+sizeof(uint64_t)+4+length)*sizeof(char)];//(char *)malloc((2+sizeof(uint64_t)+4+length)*sizeof(char));
    uint64_t len = htons64(length);
    memcpy(payload_frame, header, 2);
    memcpy(payload_frame+2, &len, sizeof(uint64_t));
    memcpy(payload_frame+2+sizeof(uint64_t), key, 4);
    memcpy(payload_frame+2+sizeof(uint64_t)+4, (const char *)mask((char *)key, payload_copy, length), length);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload_frame,length+6+sizeof(uint64_t));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();

    if(msgDatas->size() != 1) {
      printf("testFrameParser case4 size is error,now is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case4 frame check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals(payload)) {
      printf("testFrameParser case4 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
      return -1;
    }
    free(payload_copy);
  }

  //case6
  {
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";
    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload,strlen(payload));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() == 0) {
      printf("testFrameParser case7 size check failed,it is 0 \n");
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case7 frame check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case7 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
    }
  }

  //case7
  {
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";
    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)payload,strlen(payload));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() == 0) {
      printf("testFrameParser case7 size check failed,it is 0 \n");
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getData() == nullptr) {
      printf("testFrameParser case7 frame check failed frame is null \n");
      return -1;
    }

    if(!frame->getData()->toString()->equals("Hello")) {
      printf("testFrameParser case7 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
      return -1;
    }
  }
  //case 8
  {
    size_t offset = 0;
    const char *payload = "\x81\x85\x37\xfa\x21\x3d\x7f\x9f\x4d\x51\x58";
    uint16_t length = strlen(payload);
    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();

    ByteArray loadData = createByteArray((const byte *)payload,1);
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check1 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[1],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check2 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[2],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check3 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[3],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check4 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[4],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check5 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[5],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check6 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[6],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check7 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[7],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check7 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[8],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check8 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[9],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 0) {
      printf("testFrameParser case8 frame check9 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    parser->pushParseData(createByteArray((byte *)&payload[10],1));
    msgDatas = parser->doParse();
    if(msgDatas->size() != 1) {
      printf("testFrameParser case8 frame check10 size failed,current is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    String message = frame->getData()->toString();
    if(message == nullptr || !message->equals("Hello")) {
      printf("testFrameParser case8 frame check frame failed,current is %s \n",message->toChars());
      return -1;
    }

  }

  printf("testFrameParser OK \n");

  return 0;
}
