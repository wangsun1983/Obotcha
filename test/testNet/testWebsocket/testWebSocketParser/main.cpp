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

using namespace obotcha;

extern int testFrameParser();
extern int testSimpleFrameParser();
extern int testFrameParserException();
extern int testWebFrameOneByteParser();

int main() {
    testSimpleFrameParser();
	testFrameParser();
    testFrameParserException();
    testWebFrameOneByteParser();
    return 0;
}
