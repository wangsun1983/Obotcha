#include "TcpServer.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Thread.hpp"
#include "InitializeException.hpp"
#include "FileOutputStream.hpp"
#include "File.hpp"
#include "Mutex.hpp"
#include "Condition.hpp"
#include "System.hpp"
#include "TcpServer.hpp"
#include "FileOutputStream.hpp"

using namespace obotcha;

/*
sudo ufw disable
*/

//client should use 8 thread to send data
DECLARE_SIMPLE_CLASS(MyFileListener) IMPLEMENTS(SocketListener) {
public:
    _MyFileListener() {
        index = 0;
    }

    void onDataReceived(SocketResponser r,ByteArray pack) {
        stream->write(pack);
    }

    void onDisconnect(SocketResponser r) {
        printf("onDisConnect \n");
        stream->close();
        index++;
    }

    void onConnect(SocketResponser r) {
        printf("onConnect \n");
        stream = createFileOutputStream(createString(index));
        stream->open();
    }

    void onTimeout() {

    }

public:
    FileOutputStream stream;
    int index; 
};

int recvfiletest() {
  MyFileListener listener = createMyFileListener();
  TcpServer server = createTcpServer(1992,listener);
  server->start();
  while(1){sleep(100);};
  return 0;
}