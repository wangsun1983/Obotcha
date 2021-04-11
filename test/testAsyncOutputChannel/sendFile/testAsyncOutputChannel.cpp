#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "File.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

DECLARE_SIMPLE_CLASS(MyListener) IMPLEMENTS(SocketListener) {
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
    long index = 0;
 
    File file = createFile("testdata.img");
    FileInputStream inputstream = createFileInputStream(file);
    inputstream->open();
    
    while(1) {
        ByteArray data = createByteArray(1024*4);
        int length = inputstream->read(index,data);
        index += length;
        //printf("start write,data size is %d,length is %d,index is %ld \n",data->size(),length,index);
        stream->write(data,length);
        if(index >= file->length()) {
            break;
        }
    }

    printf("index is %ld \n",index);

    while(1) {
        sleep(1);
    }
}
