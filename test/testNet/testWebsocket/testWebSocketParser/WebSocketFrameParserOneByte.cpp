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


int testWebFrameOneByteParser() {
  //case 1
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
      ArrayList<WebSocketFrame> msgDatas = createArrayList<WebSocketFrame>();

      for(int i = 0;i<(2+2+4+length);i++) {
        ByteArray loadData = createByteArray(1);
        loadData[0] = payload_frame[i];
        parser->pushParseData(loadData);
        ArrayList<WebSocketFrame> datas = parser->doParse();
        msgDatas->add(datas);
      }
/*
      ByteArray loadData = createByteArray((const byte *)payload_frame,(2+2+4+length));
      parser->pushParseData(loadData);
      ArrayList<WebSocketFrame> msgDatas = parser->doParse();
*/
      if(msgDatas->size() != 1) {
        printf("testFrameOneByteParser case3 size is error,now is %d \n",msgDatas->size());
        return -1;
      }

      WebSocketFrame frame = msgDatas->get(0);
      if(frame->getData() == nullptr) {
        printf("testFrameOneByteParser case3 frame check failed frame is null \n");
        return -1;
      }

      if(!frame->getData()->toString()->equals(payload)) {
        printf("testFrameOneByteParser case3 frame check failed frame is %s \n",frame->getData()->toString()->toChars());
        return -1;
      }
      free(payload_copy);
  }


  printf("testFrameOneByteParser OK \n");

  return 0;
}
