#include "DatagramSocketImpl.hpp"
#include "SocketBuilder.hpp"
#include "SocketMonitor.hpp"
#include "Handler.hpp"
#include "Inet4Address.hpp"
#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "System.hpp"
#include "Md.hpp"

using namespace obotcha;

int main() {
    //prepare file
    File file = createFile("data");

    if(!file->exists()) {
      file->createNewFile();
        for(int i = 0;i<1024;i++) {
        FileOutputStream stream = createFileOutputStream(file);
        stream->open(st(OutputStream)::Append);
        String data = createString("");
        for(int i = 0;i < 1024;i++) {
          data = data->append(createString(st(System)::currentTimeMillis()));
        }
        stream->write(data->toByteArray());
        stream->close();
      }
    }

    InetAddress addr = createInet4Address(1234);
    Socket client = createSocketBuilder()->setAddress(addr)->newDatagramSocket();

    int ret = client->connect();
    String resp = createString("hello server");
    ByteArray fileBuff = createByteArray(1024*4);
    FileInputStream stream = createFileInputStream(file);
    stream->open();
    long index = 0;
    long filesize = file->length();
    while(1) {
      long length = stream->readTo(fileBuff);
      int ret = client->getOutputStream()->write(fileBuff);
      filesize -= length;
      usleep(100*1000);
      if(filesize == 0) {
        break;
      }
    }
    stream->close();

    usleep(1000*1000);
    Md md5 = createMd();
    String v1 = md5->encrypt(createFile("data"));
    String v2 = md5->encrypt(createFile("file"));

    if(v1 != v2) {
      printf("---TestDataGramSocket case2_simple_send_file_delayed test1 [FAILED]---,v1 is %s,v2 is %s \n",v1->toChars(),v2->toChars());
      return 0;
    }

    printf("---TestDataGramSocket case2_simple_send_file_delayed test100 [OK]--- \n");
    return 0;
    return 0;
}