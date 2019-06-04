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

static Mutex mutex = createMutex("FileWatchMutex");

_FileWatcher *_FileWatcher::instance = nullptr;

_FileWatcher::_FileWatcher() {
    mlisteners = createHashMap<int,FileObserver>();
    openInotifyDev();
    start();
}

sp<_FileWatcher> _FileWatcher::getInstance() {
    if(instance != nullptr) {
        sp<_FileWatcher> s;
        s.set_pointer(instance);
        return s;
    }

    AutoMutex l(mutex);
    instance = new _FileWatcher();
    return instance;
}

int _FileWatcher::startWatch(String filepath,int op,sp<_FileObserver> observer) {
    AutoMutex l(mutex);

    int id = inotify_add_watch(notifyFd,filepath->toChars(),op);
    
    mlisteners->put(id,observer);
    return id;
    //printf("watch file is %s \n",filepath->toChars());
    //inotify_add_watch(notifyFd,filepath->toChars(),op);
}

void _FileWatcher::stopWatch(int id) {
    AutoMutex l(mutex);

    mlisteners->remove(id);

    //inotify_rm_watch(filepath->toChars());
}


void _FileWatcher::openInotifyDev() {
    notifyFd = inotify_init(); 
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
        printf("inotify ... len is %d\n",len);
        int nread = 0;
        while (len > 0) {
            struct inotify_event * event = (struct inotify_event *)&buf[nread];
            char *p = event->name;
            printf("name is %s,event->len is %d \n",p,event->len);

            String filepath = createString(event->name);
            while(1){
                AutoMutex l(mutex);
                int changeid = event->wd;
                FileObserver observer = mlisteners->get(changeid);

                if(observer != nullptr) {
                    observer->onFileUpdate(filepath,event->mask);
                }
                /*
                HashMap<int,ArrayList<FileObserver>> map = mlisteners->get(filepath);
                printf("inotify ...1 event is %d,path is %s \n",event->mask,event->name);
                if(map == nullptr) {
                    break;
                }
                printf("inotify ...2 \n");
                ArrayList<FileObserver> list = map->get(event->mask);
                if(list == nullptr) {
                    break;
                }
                printf("inotify ...3 \n");
                ListIterator<FileObserver> iterator = list->getIterator();
                while(iterator->hasValue()) {
                    FileObserver observer = iterator->getValue();
                    printf("inotify ...4 \n");
                    observer->onFileUpdate(filepath,event->mask);
                    iterator->next();
                }
                */

                break;
            }
            
            nread = nread + sizeof(struct inotify_event) + event->len;
            len = len - sizeof(struct inotify_event) - event->len;
            printf("len is %d \n",len);
        }
    }
}

}
