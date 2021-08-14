#include <stdio.h>
#include <unistd.h>

#include "StrongPointer.hpp"
#include "Long.hpp"
#include "Log.hpp"
#include "Thread.hpp"
#include "SpinLock.hpp"
#include "AutoLock.hpp"
#include "TimeWatcher.hpp"

using namespace obotcha;

int testSpinlockLock() {
	TimeWatcher watcher = createTimeWatcher();

	while(1) {
		SpinLock l = createSpinLock();
		Thread t = createThread([&l]{
			l->lock();
			usleep(200*1000);
			l->unlock();
		});
		t->start();
		usleep(100*1000);

		watcher->start();
		l->lock();
		long v = watcher->stop();
		if(v < 100 || v > 105) {
			printf("---[TestSpinlock Lock case1] [FAILED]--- \n");
			break;
		}
		l->unlock();
		break;
	}

	printf("---[TestSpinlock Lock case100] [OK]--- \n");
}
