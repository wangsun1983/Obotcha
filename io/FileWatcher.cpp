/**
 * @file FileWatcher.cpp
 * @brief Monitors files (using <a href="http://en.wikipedia.org/wiki/Inotify">inotify</a>)
 *        to fire an event after files are accessed or changed by any process on
 *        the device (including this one). 
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 */
#include "FileWatcher.hpp"
#include "Log.hpp"

namespace obotcha {

void _FileUpdateListener::setPath(String p) {
    mPath = p;
}

String _FileUpdateListener::getPath() {
    return mPath;
}

void _FileUpdateListener::setOperations(int p) {
    mOperations = p;
}

int _FileUpdateListener::getOperations() {
    return mOperations;
}

//FileWatcher
_FileWatcher::_FileWatcher() {
    notifyFd = inotify_init();
    mObserver = createEPollObserver();
    mObserver->addObserver(notifyFd,EPOLLIN,AutoClone(this));
}

int _FileWatcher::stopWatch(int id) {
    AutoLock l(mutex);
    mNodes->remove(id);
    return inotify_rm_watch(notifyFd, id);
}

void _FileWatcher::close() {
    mObserver->close();
    AutoLock l(mutex);
    mNodes->clear();
}

st(IO)::Epoll::Result _FileWatcher::onEvent(int fd, uint32_t events) {
    struct inotify_event *event;
    char event_buf[sizeof(inotify_event)*128] = {0};

    int event_pos = 0;
    ssize_t num_bytes = read(fd, event_buf, sizeof(event_buf));
    if (num_bytes < sizeof(*event)) {
        if (errno == EINTR)
            return st(IO)::Epoll::Result::Ok;

        LOG(ERROR) << "***** ERROR! got a short event!";
        st(IO)::Epoll::Result::Remove;
    }

    while (num_bytes >= sizeof(*event)) {
        event = (struct inotify_event *)(event_buf + event_pos);
        int event_size = sizeof(*event) + event->len;
        int changeid = event->wd;
        {
            AutoLock l(mutex);
            auto listener = mNodes->get(changeid);
            if(listener != nullptr) {
                // when vim/gedit opens a file ,it will create a bak file.
                // if the edited file is saved,vim/gedit will delete the origin
                // file,and change the bak file to origin file.
                // this is the reason why use vim/gedit to modify a file,inotify
                // only accepts IGNORE event.
                int ignoreid = -1;
                if ((access(listener->getPath()->toChars(), F_OK) == 0) &&
                    ((event->mask & Ignored) != 0)) {
                    event->mask &= ~Ignored;
                    event->mask |= Modify;
                    ignoreid = inotify_add_watch(notifyFd, 
                                                listener->getPath()->toChars(),
                                                listener->getOperations());
                }

                if (ignoreid != -1) {
                    listener->onFileUpdate(listener->getPath(),event->mask,changeid,ignoreid);
                    inotify_rm_watch(notifyFd, changeid);
                    mNodes->remove(changeid);
                    mNodes->put(ignoreid,listener);
                } else {
                    listener->onFileUpdate(listener->getPath(),event->mask,changeid,changeid);
                }
            }
        }
        
        num_bytes -= event_size;
        event_pos += event_size;
    }

    return st(IO)::Epoll::Result::Ok;
}

} // namespace obotcha
