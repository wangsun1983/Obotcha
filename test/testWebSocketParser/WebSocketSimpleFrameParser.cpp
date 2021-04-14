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

      if(frame->getData() == nullptr || !frame->getData()->equals("Hello")) {
        printf("testSimpleFrameParser case2  error,frame is %s\n",frame->getData()->toChars());
        return -1;
      }

      //printf("msg is %s\n",frame->getData()->toChars());

  }
#endif

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

  return 0;

}
