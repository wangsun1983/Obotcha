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
    printf("trace1 !!! \n");
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();
    printf("trace2 !!!,msgData size is %d \n",msgDatas->size());
    WebSocketFrame frame = msgDatas->get(0);

    printf("frame is %s \n",frame->getMessage()->toChars());
  }
  //case 2
#if 0
  {
      size_t offset = 0;
      const char *header = "\x81\xFE";
      const char *key = "\x37\xfa\x21\x3d";
      const char *payload = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin hendrerit ornare tortor ut euismod. Nunc finibus convallis sem, at imperdiet ligula commodo id. Nam bibendum nec augue in posuere mauris.";
      uint16_t length = strlen(payload);
      char *payload_copy = (char *)WSS_copy((void *)payload, length);
      char *payload_frame = (char *)malloc((2+2+4+length+1)*sizeof(char));
      uint16_t len = htons(length);
      memcpy(payload_frame, header, 2);
      memcpy(payload_frame+2, &len, 2);
      memcpy(payload_frame+2+2, key, 4);
      memcpy(payload_frame+2+2+4, (const char *)mask(key, payload_copy, length), length);

  }
#endif


}
