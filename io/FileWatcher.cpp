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


namespace obotcha {

_FileWatcher::_FileWatcher() {
    mutex = createMutex("FileWatchMutex");
    mListeners = createHashMap<int,ArrayList<sp<_FileObserver>>>();
    notifyFd = inotify_init(); 
    start();
}

int _FileWatcher::startWatch(String filepath,int op,sp<_FileObserver> observer) {
    AutoLock l(mutex);
    printf("startWatch op code is %x \n",op);
    int id = inotify_add_watch(notifyFd,filepath->toChars(),op);
    if(std::find(observer->ids.begin(),observer->ids.end(),id) != observer->ids.end()) {
        return id;
    }

    observer->ids.push_back(id);
    printf("startWatch trace \n");
    ArrayList<FileObserver> list = mListeners->get(id);
    if(list == nullptr) {
        list = createArrayList<FileObserver>();
        mListeners->put(id,list);
    }

    list->add(observer);
    return id;
}

void _FileWatcher::stopWatch(int id,FileObserver observer) {
    AutoLock l(mutex);

    ArrayList<FileObserver> list = mListeners->get(id);
    if(list != nullptr) {
        ListIterator<FileObserver> iterator = list->getIterator();
        while(iterator->hasValue()) {
            FileObserver monitor = iterator->getValue();
            if(monitor == observer) {
                iterator->remove();
                continue;
            }
            iterator->next();
        }
    }

    if(list->size() == 0) {
        inotify_rm_watch(notifyFd,id);
    }
}

void _FileWatcher::release() {
    AutoLock l(mutex);
    mListeners->clear();
    close(notifyFd);
    quit();
}

void _FileWatcher::run() {

    char event_buf[512];
    struct inotify_event* event;

    while (1) {
        int event_pos = 0;
        printf("abc trace1 \n");
        int num_bytes = read(notifyFd, event_buf, sizeof(event_buf));

        if (num_bytes < (int)sizeof(*event)) {
            if (errno == EINTR)
                continue;

            LOG(ERROR)<<"***** ERROR! got a short event!";
            return;
        }

        while (num_bytes >= (int)sizeof(*event)) {
            int event_size;
            event = (struct inotify_event *)(event_buf + event_pos);

            String path = createString(event->name);
            int wd = event->wd;
            {
                AutoLock l(mutex);
                int changeid = event->wd;
                ArrayList<FileObserver> monitors = mListeners->get(changeid);
                if(monitors != nullptr) {
                    ListIterator<FileObserver> iterator = monitors->getIterator();
                    while(iterator->hasValue()) {
                        FileObserver monitor = iterator->getValue();
                        monitor->onFileUpdate(path,event->mask);
                        iterator->next();
                    }
                }
                printf("abc trace3 \n");
            }

            event_size = sizeof(*event) + event->len;
            num_bytes -= event_size;
            event_pos += event_size;
            printf("abc trace4 \n");
        }
    }
}



}
