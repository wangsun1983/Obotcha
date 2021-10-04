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
#include "AtomicInteger.hpp"
#include "CountDownLatch.hpp"
#include "WebSocketServerBuilder.hpp"
#include "System.hpp"
#include "Md.hpp"

using namespace obotcha;

CountDownLatch latch = createCountDownLatch(1);

DECLARE_CLASS(MyWsListener) IMPLEMENTS(WebSocketListener) {
public:
    _MyWsListener() {
        File f = createFile("./tmp/rcvfile");
        if(f->exists()) {
            f->removeAll();
        }
        f->createNewFile();

        stream = createFileOutputStream(f);
        stream->open();
    }

    int onData(WebSocketFrame message,WebSocketLinker client) {
        stream->write(message->getData());
        return 0;
    }

    int onConnect(WebSocketLinker client) {
        return 0;
    }

    int onDisconnect(WebSocketLinker client) {
        latch->countDown();
        return 0;
    }

    int onPong(WebSocketLinker client) {
        return 0;
    }

    int onPing(WebSocketLinker client) {
        return 0;
    }

private:
    FileOutputStream stream;
};



int main() {
    //crete file first
    File file = createFile("./tmp/data");
    long prepareFilesize = file->length();

    if(!file->exists()) {
        file->createNewFile();
        for(int i = 0;i<1024;i++) {
            FileOutputStream stream = createFileOutputStream(file);
            stream->open(st(OutputStream)::Append);
            String data = createString("");
            for(int j = 0;j < 256;j++) {
                data = data->append(createString(st(System)::currentTimeMillis()));
            }
            stream->write(data->toByteArray());
            stream->close();
        }
    }


    MyWsListener l = createMyWsListener();

    InetAddress address = createInetAddress(1111);
    WebSocketServer server = createWebSocketServerBuilder()
                            ->setInetAddr(address)
                            ->addListener("mytest",l)
                            ->build();

    server->start();

    latch->await();

    //check md5
    Md md5 = createMd();
    String base = md5->encrypt(createFile("./tmp/data"));
    String rcv = md5->encrypt(createFile("./tmp/rcvfile"));
    if(!base->equals(rcv)) {
        printf("---WebSocketServer MultiThread test1 [FAILED]--- \n");
    }

    printf("---WebSocketServer MultiThread test100 [OK]--- \n");
}
