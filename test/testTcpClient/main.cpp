
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "TcpClient.hpp"
#include "Thread.hpp"
#include "System.hpp"
#include "TcpServer.hpp"
#include "InitializeException.hpp"

using namespace obotcha;

extern int testTcpClient();
extern int testTcpClientSync();

int main() {
    testTcpClient();
    //testTcpClientSync();
    
}
