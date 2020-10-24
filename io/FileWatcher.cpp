#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>


#include "FileWatcher.hpp"
#include "Object.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "FileWatcher.hpp"

#define INOTIFY_EVENT_SIZE 1024*32

namespace obotcha {

Mutex _FileWatcher::mInitMutex = createMutex("FileWatcherInitMutex");
sp<_FileWatcher> _FileWatcher::mInstance = nullptr; 


_FileWatcher::_FileWatcher() {
    mutex = createMutex("FileWatchMutex");
    mListeners = createHashMap<int,ArrayList<LocalFileObserverMonitor>>();
    notifyFd = inotify_init(); 
    start();
}

sp<_FileWatcher> _FileWatcher::getInstance() {
    if(mInstance != nullptr) {
        return mInstance;
    }

    AutoLock l(mInitMutex);
    if(mInstance != nullptr) {
        return mInstance;
    }

    _FileWatcher *p = new _FileWatcher();
    mInstance.set_pointer(p);
    return mInstance;
}

int _FileWatcher::startWatch(String filepath,int op,sp<_FileObserver> observer) {
    AutoLock l(mutex);
    LocalFileObserverMonitor monitor = createLocalFileObserverMonitor();
    monitor->op = op;
    monitor->mObserver = observer;

    int id = inotify_add_watch(notifyFd,filepath->toChars(),op);

    ArrayList<LocalFileObserverMonitor> list = mListeners->get(id);
    if(list == nullptr) {
        list = createArrayList<LocalFileObserverMonitor>();
        mListeners->put(id,list);
    }

    list->add(monitor);
    return id;
}

void _FileWatcher::stopWatch(int id,int op,FileObserver observer) {
    AutoLock l(mutex);
    ArrayList<LocalFileObserverMonitor> list = mListeners->get(id);
    if(list != nullptr) {
        ListIterator<LocalFileObserverMonitor> iterator = list->getIterator();
        while(iterator->hasValue()) {
            LocalFileObserverMonitor monitor = iterator->getValue();
            if(monitor->mObserver == observer) {
                monitor->op &= ~op;
            }

            if(monitor->op == 0) {
                iterator->remove();
                continue;
            }
            iterator->next();
        }
    }

    if(list->size() == 0) {
        inotify_rm_watch(notifyFd,id);
    }

    //mlisteners->remove(id);
    //inotify_rm_watch(filepath->toChars());
}

int _FileWatcher::closeInotifyDev() {
    int r;
    if ((r = close (notifyFd)) < 0) {
        perror ("close (fd) = ");
    }

    return r;
}

void _FileWatcher::run() {
    char buf[INOTIFY_EVENT_SIZE];
    int len = 0;

    while ((len = read(notifyFd, buf, INOTIFY_EVENT_SIZE - 1)) > 0) {
        int nread = 0;
        while (len > 0) {
            struct inotify_event * event = (struct inotify_event *)&buf[nread];
            char *p = event->name;
        
            String filepath = createString(event->name);
            while(1){
                AutoLock l(mutex);
                int changeid = event->wd;
                ArrayList<LocalFileObserverMonitor> monitors = mListeners->get(changeid);

                if(monitors != nullptr) {
                    ListIterator<LocalFileObserverMonitor> iterator = monitors->getIterator();
                    while(iterator->hasValue()) {
                        LocalFileObserverMonitor monitor = iterator->getValue();
                        int action = (monitor->op & event->mask);
                        if(action != 0) {
                            monitor->mObserver->onFileUpdate(filepath,action);
                        }
                        iterator->next();
                    }
                }
                break;
            }
            
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
        }
    }
}

}
