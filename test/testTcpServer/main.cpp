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

using namespace obotcha;

/*

sudo ufw disable
*/
extern int normaltest();
extern int recvfiletest();

int main() {
  //normaltest();
  recvfiletest();
  return 0;
}