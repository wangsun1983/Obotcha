#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"

using namespace obotcha;

DECLARE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
public:
    void onSocketMessage(int,Socket,ByteArray) {

    }
};

int main() {
    Socket s = createSocketBuilder()
                ->setAddress(createInetAddress(createString("192.168.1.6"),1234))
                ->newSocket();

    s->connect();

    SocketMonitor monitor = createSocketMonitor();
    monitor->bind(s,createMyListener());
    
    OutputStream stream = s->getOutputStream();
    int index = 0;

    while(index < 1024*32) {
        String data = createString("abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz abcdefghijklmn opqrst uvwxyz what this is index:")->append(createString(index),createString("\n"));
        index++;
        stream->write(createByteArray(data));
    }

    while(1) {
        sleep(1);
    }
}
