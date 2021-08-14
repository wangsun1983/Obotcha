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

int testSpinlockTryLock() {
	TimeWatcher watcher = createTimeWatcher();

	while(1) {
		SpinLock l = createSpinLock();
		Thread t = createThread([l]{
			l->lock();
			usleep(200*1000);
			l->unlock();
		});
		t->start();
		usleep(100*1000);

		watcher->start();
		int ret = l->tryLock();
		long v = watcher->stop();
		if(v < 0 || v > 5) {
			printf("---[TestSpinlock TryLock case1] [FAILED]--- \n");
			break;
		}

		if(ret != -LockBusy) {
			printf("---[TestSpinlock TryLock case2] [FAILED]--- \n");
			break;
		}

		break;
	}

	while(1) {
		SpinLock l = createSpinLock();
		Thread t = createThread([&l]{
			l->tryLock();
			usleep(200*1000);
			l->unlock();
		});
		t->start();

		usleep(100*1000);
		watcher->start();
		l->lock();
		long v = watcher->stop();
		if(v < 100 || v > 105) {
			printf("---[TestSpinlock TryLock case3] [FAILED]---,v is %d \n",v);
			break;
		}
		t->join();
		break;
	}

	printf("---[TestSpinlock TryLock case100] [OK]--- \n");
}
