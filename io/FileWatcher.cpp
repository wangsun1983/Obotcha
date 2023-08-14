#include "FileWatcher.hpp"
#include "Log.hpp"
#include "InfiniteLoop.hpp"

namespace obotcha {

//FileUpdateNode
_FileUpdateNode::_FileUpdateNode(FileUpdateListener listener,
                                 String filepath,
                                 int operation):l(listener),
                                                path(filepath),
                                                operations(operation) {
}

//FileWatcher
_FileWatcher::_FileWatcher() {
    notifyFd = inotify_init();
    start();
}

int _FileWatcher::startWatch(String filepath, int op,FileUpdateListener l) {
    AutoLock lock(mutex);
    int id = inotify_add_watch(notifyFd, filepath->toChars(), op);
    auto node = createFileUpdateNode(l,filepath,op);
    mNodes->put(id,node);
    return id;
}

void _FileWatcher::stopWatch(int id) {
    AutoLock l(mutex);
    mNodes->remove(id);
}

void _FileWatcher::close() {
    AutoLock l(mutex);
    mNodes->clear();
    ::close(notifyFd);
}

void _FileWatcher::run() {
    char event_buf[512] = {0};
    struct inotify_event *event;

    InfiniteLoop {
        int event_pos = 0;
        ssize_t num_bytes = read(notifyFd, event_buf, sizeof(event_buf));
        if (num_bytes < sizeof(*event)) {
            if (errno == EINTR)
                continue;

            LOG(ERROR) << "***** ERROR! got a short event!";
            return;
        }
        while (num_bytes >= sizeof(*event)) {
            int event_size;
            event = (struct inotify_event *)(event_buf + event_pos);
            int changeid = event->wd;
            {
                AutoLock l(mutex);
                FileUpdateNode node = mNodes->get(changeid);
                if(node == nullptr) {
                    continue;
                }
                // when vim/gedit opens a file ,it will create a bak file.
                // if the edited file is saved,vim/gedit will delete the origin
                // file,and change the bak file to origin file.
                // this is the reason why use vim/gedit to modify a file,inotify
                // only accepts IGNORE event.
                int ignoreid = -1;
                if ((access(node->path->toChars(), F_OK) == 0) &&
                    ((event->mask & Ignored) != 0)) {
                    event->mask &= ~Ignored;
                    event->mask |= Modify;
                    ignoreid = inotify_add_watch(notifyFd, 
                                                node->path->toChars(),
                                                node->operations);
                }

                if (ignoreid != -1) {
                    node->l->onFileUpdate(node->path,event->mask,changeid,ignoreid);
                    inotify_rm_watch(notifyFd, changeid);
                    mNodes->remove(changeid);
                    mNodes->put(ignoreid,node);
                } else {
                    node->l->onFileUpdate(node->path,event->mask,changeid,changeid);
                }
            }

            event_size = sizeof(*event) + event->len;
            num_bytes -= event_size;
            event_pos += event_size;
        }
    }
}

} // namespace obotcha
