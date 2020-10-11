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
#include "WebSocketFrameComposer.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketComposer.hpp"
#include "File.hpp"
#include "FileOutputStream.hpp"
#include "AtomicLong.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(WsCommands){
public:
    static const int RequestClearRecords = 1000;
    static const int RequestStatistics = 1001;
    static const int RequestReply = 1002;

public:
    static const int ResponseStatistics = 2001;
    static const int ResponseReply = 2002;

};