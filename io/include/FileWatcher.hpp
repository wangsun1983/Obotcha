#ifndef __OBOTCHA_FILE_OBSERVER_HPP__
#define __OBOTCHA_FILE_OBSERVER_HPP__

#include <sys/inotify.h>

#include "Object.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "String.hpp"
#include "Thread.hpp"

namespace obotcha {

class _FileWatcher;

DECLARE_CLASS(FileUpdateListener) {
public:
    friend class _FileWatcher;
    virtual void onFileUpdate(String filepath, int op,int origid,int currentid) = 0;
};

DECLARE_CLASS(FileUpdateNode) {
public:
    _FileUpdateNode(FileUpdateListener,String,int);
    FileUpdateListener l;
    String path;
    int operations;
};

DECLARE_CLASS(FileWatcher) IMPLEMENTS(Thread) {
  public:
    enum FileWatchType {
        Access = IN_ACCESS,              /* File was accessed.  */
        Modify = IN_MODIFY,              /* File was modified.  */
        Attrib = IN_ATTRIB,              /* Metadata changed.  */
        CloseWrite = IN_CLOSE_WRITE,     /* Writtable file was closed.  */
        CloseNoWrite = IN_CLOSE_NOWRITE, /* Unwrittable file closed.  */
        Close = IN_CLOSE,                /* Close.  */
        Open = IN_OPEN,                  /* File was opened.  */
        MovedFrom = IN_MOVED_FROM,       /* File was moved from X.  */
        MovedTo = IN_MOVED_TO,           /* File was moved to Y.  */
        Move = IN_MOVE,                  /* Moves.  */
        Create = IN_CREATE,              /* Subfile was created.  */
        Delete = IN_DELETE,              /* Subfile was deleted.  */
        DeleteSelf = IN_DELETE_SELF,     /* Self was deleted.  */
        MoveSelf = IN_MOVE_SELF,         /* Self was moved.  */
        UnMount = IN_UNMOUNT,            /* Backing fs was unmounted.  */
        OverFlow = IN_Q_OVERFLOW,        /* Event queued overflowed.  */
        Ignored = IN_IGNORED,            /* File was ignored.  */
    };

    const static int Full = Access | Modify | Attrib | CloseWrite |
                            CloseNoWrite | Close | Open | MovedFrom | MovedTo |
                            Move | Create | Delete | DeleteSelf | MoveSelf |
                            UnMount | OverFlow | Ignored;

    const static int EventNum = 17;

    _FileWatcher();

    int startWatch(String filepath, int op, FileUpdateListener observer);

    void stopWatch(int id);

    void close();

  private:
    void run();

    int notifyFd;

    Mutex mutex;

    void handleEvent(struct inotify_event * event);

    int readEvent();

    HashMap<int, FileUpdateNode> mNodes;
};

} // namespace obotcha
#endif
