#include <stdio.h>
#include <unistd.h>

#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "Thread.hpp"
#include "SpinLock.hpp"
#include "AutoLock.hpp"

using namespace obotcha;

SpinLock lock1;

DECLARE_SIMPLE_CLASS(Thread1) EXTENDS(Thread) {
public:
	void run() {
		LOG(ERROR)<<"i run1";
		sleep(1);
		LOG(ERROR)<<"i run2";
		AutoLock l(lock1);
		LOG(ERROR)<<"i run3";
	}
};

int main() {

	lock1 = createSpinLock();
    Thread1 t1 = createThread1();
    t1->start();
    {
    	AutoLock l(lock1);
    	LOG(ERROR)<<"i sleep1";
    	sleep(5);
    	LOG(ERROR)<<"i sleep2";
    }
    
    while(1) {sleep(1000);}
}
