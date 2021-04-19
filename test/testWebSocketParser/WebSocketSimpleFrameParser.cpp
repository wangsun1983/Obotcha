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
#include "WebSocketProtocol.hpp"

using namespace obotcha;

struct scripted_data_feed {
  uint8_t data[8192];
  uint8_t* datamark;
  uint8_t* datalimit;
  size_t feedseq[8192];
  size_t seqidx;
};

static void scripted_data_feed_init(struct scripted_data_feed *df,
                                    uint8_t *data, size_t data_length)
{
  memset(df, 0, sizeof(struct scripted_data_feed));
  memcpy(df->data, data, data_length);
  df->datamark = df->data;
  df->datalimit = df->data+data_length;
  df->feedseq[0] = data_length;
}

int testSimpleFrameParser() {

#if 0
  //case 1
  {
      uint8_t msg[] = { 0x81u, 0x85u, 0x37u, 0xfau, 0x21u, 0x3du, 0x7fu, 0x9fu,
                    0x4du, 0x51u, 0x58u };
      WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
      ByteArray loadData = createByteArray((const byte *)msg,sizeof(msg)/sizeof(uint8_t));
      parser->pushParseData(loadData);
      ArrayList<WebSocketFrame> msgDatas = parser->doParse();
      WebSocketFrame frame = msgDatas->get(0);
      if(frame->getHeader()->getOpCode() != 0x1) {
        printf("testSimpleFrameParser case1 opcode  error,opcode is %d\n",frame->getHeader()->getOpCode());
        return -1;
      }

      if(frame->getData() == nullptr || !frame->getData()->toString()->equals("Hello")) {
        printf("testSimpleFrameParser case2  error,frame is %s\n",frame->getData()->toString()->toChars());
        return -1;
      }

      //printf("msg is %s\n",frame->getData()->toChars());

  }


  //case 2
  {
    uint8_t msg[] = { 0x01, 0x03, 0x48, 0x65, 0x6c, /* "Hel" */
                    0x80, 0x02, 0x6c, 0x6f }; /* "lo" */

    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)msg,sizeof(msg)/sizeof(uint8_t));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getHeader()->getOpCode() != 0x1) {
      printf("testSimpleFrameParser case2 opcode  error,opcode is %d\n",frame->getHeader()->getOpCode());
      return -1;
    }

    if(frame->getData() == nullptr || !frame->getData()->toString()->equals("Hel")) {
      printf("testSimpleFrameParser case2  error,frame is %s\n",frame->getData()->toString()->toChars());
      return -1;
    }

    frame = msgDatas->get(1);
    printf("opcode is %d,length is %d \n",frame->getHeader()->getOpCode(),frame->getHeader()->getFrameLength());

    if(frame->getHeader()->getOpCode() != 0x0) {
      printf("testSimpleFrameParser case2 trace1 opcode  error,opcode is %d\n",frame->getHeader()->getOpCode());
      return -1;
    }

    if(frame->getData() == nullptr ) {
      printf("testSimpleFrameParser case2  trace1 error,tframe is nullptr\n");
      return -1;
    }
  }

  //case 3
  {
    uint8_t msg[] = { 0x01, 0x03, 0x48, 0x65, 0x6c, /* "Hel" */
                  /* ping with "Hello" */
                  0x89, 0x05, 0x48, 0x65, 0x6c, 0x6c, 0x6f,
                  0x80, 0x02, 0x6c, 0x6f }; /* "lo" */

    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)msg,sizeof(msg)/sizeof(uint8_t));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();

    if(msgDatas->size() != 3) {
      printf("testSimpleFrameParser case3 trace1 size is error,current is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    if(frame->getHeader()->isFinalFrame()) {
      printf("testSimpleFrameParser case3 trace2 not final frame \n");
      return -1;
    }

    ByteArray data = frame->getData();
    if(data == nullptr || !data->toString()->equals("Hel")) {
      printf("testSimpleFrameParser case3 trace3 frame content is not equal \n");
      return -1;
    }

    if(frame->getHeader()->getOpCode() != st(WebSocketProtocol)::OPCODE_TEXT) {
      printf("testSimpleFrameParser case3 trace4 opcode is error,current is %d \n",frame->getHeader()->getOpCode());
      return -1;
    }

    frame = msgDatas->get(1);
    if(!frame->getHeader()->isFinalFrame()) {
      printf("testSimpleFrameParser case3 trace5 not final frame \n");
      return -1;
    }

    data = frame->getData();
    printf("data is %d \n",data->size());
    if(data == nullptr || !data->toString()->equals("Hello")) {
      printf("testSimpleFrameParser case3 trace6 frame content is not equal \n");
      return -1;
    }

    if(frame->getHeader()->getOpCode() != st(WebSocketProtocol)::OPCODE_CONTROL_PING) {
      printf("testSimpleFrameParser case3 trace7 opcode is error,current is %d \n",frame->getHeader()->getOpCode());
      return -1;
    }

    frame = msgDatas->get(2);
    if(!frame->getHeader()->isFinalFrame()) {
      printf("testSimpleFrameParser case3 trace8 not final frame \n");
      return -1;
    }

    data = frame->getData();
    if(data == nullptr || !data->toString()->equals("lo")) {
      printf("testSimpleFrameParser case3 trace9 frame content is not equal \n");
      return -1;
    }

    if(frame->getHeader()->getOpCode() != st(WebSocketProtocol)::OPCODE_CONTINUATION) {
      printf("testSimpleFrameParser case3 trace10 opcode is error,current is %d \n",frame->getHeader()->getOpCode());
      return -1;
    }
  }

  //case4
  {
    uint8_t msg[] = { 0x81, 0x00 };

    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)msg,sizeof(msg)/sizeof(uint8_t));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();

    if(msgDatas->size() != 1) {
      printf("testSimpleFrameParser case4 trace1 frame size,current is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    ByteArray data = frame->getData();
    if(data != nullptr && data->size() != 0) {
      printf("testSimpleFrameParser case4 trace2 data size is incorrect \n");
      return -1;
    }
  }
 #endif

  //case5
  {
    uint8_t msg[] = { 0x81, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

    WebSocketHybi13Parser parser = createWebSocketHybi13Parser();
    ByteArray loadData = createByteArray((const byte *)msg,sizeof(msg)/sizeof(uint8_t));
    parser->pushParseData(loadData);
    ArrayList<WebSocketFrame> msgDatas = parser->doParse();

    if(msgDatas->size() != 1) {
      printf("testSimpleFrameParser case5 trace1 frame size,current is %d \n",msgDatas->size());
      return -1;
    }

    WebSocketFrame frame = msgDatas->get(0);
    ByteArray data = frame->getData();
    if(data != nullptr && data->size() != 0) {
      printf("testSimpleFrameParser case5 trace2 data size is incorrect \n");
      return -1;
    }
  }

  return 0;

}
