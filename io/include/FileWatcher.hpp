#ifndef __OBOTCHA_FILE_OBSERVER_HPP__
#define __OBOTCHA_FILE_OBSERVER_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <sys/inotify.h>

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"
#include "Thread.hpp"
#include "Mutex.hpp"
#include "AutoLock.hpp"
#include "HashMap.hpp"
#include "ArrayList.hpp"

namespace obotcha {

class _FileWatcher;

DECLARE_SIMPLE_CLASS(FileObserver) {
public:
    friend class _FileWatcher;
    virtual void onFileUpdate(String filepath,int op) = 0;

private:
    std::vector<int> ids;
};

DECLARE_SIMPLE_CLASS(FileWatcher) IMPLEMENTS(Thread) {
public:
    enum FileWatchType {
        Access = IN_ACCESS,                /* File was accessed.  */
        Modify = IN_MODIFY,                /* File was modified.  */
        Attrib = IN_ATTRIB,                /* Metadata changed.  */
        CloseWrite = IN_CLOSE_WRITE,       /* Writtable file was closed.  */
        CloseNoWrite = IN_CLOSE_NOWRITE,   /* Unwrittable file closed.  */
        Close = IN_CLOSE,                  /* Close.  */
        Open = IN_OPEN,                    /* File was opened.  */
        MovedFrom = IN_MOVED_FROM,         /* File was moved from X.  */
        MovedTo = IN_MOVED_TO,             /* File was moved to Y.  */
        Move = IN_MOVE,                    /* Moves.  */
        Create = IN_CREATE,                /* Subfile was created.  */
        Delete = IN_DELETE,                /* Subfile was deleted.  */
        DeleteSelf = IN_DELETE_SELF,       /* Self was deleted.  */
        MoveSelf = IN_MOVE_SELF,           /* Self was moved.  */
        UnMount = IN_UNMOUNT,              /* Backing fs was unmounted.  */
        OverFlow = IN_Q_OVERFLOW,          /* Event queued overflowed.  */
        Ignored = IN_IGNORED,              /* File was ignored.  */
    };
    
    const static int Full = Access|Modify|Attrib|CloseWrite
                            |CloseNoWrite|Close|Open|MovedFrom
                            |MovedTo|Move|Create|Delete
                            |DeleteSelf|MoveSelf|UnMount|OverFlow
                            |Ignored;

    const static int EventNum = 17;
    
    _FileWatcher();
    
    int startWatch(String filepath,int op,sp<_FileObserver> observer);

    void stopWatch(int id,sp<_FileObserver> observer);

    void release();

private:

    void run();

    int notifyFd;



    Mutex mutex;

    void handleEvent(struct inotify_event *event);

    int readEvent();

    HashMap<int,ArrayList<sp<_FileObserver>>> mListeners;
    HashMap<int,String> mFiles;
    HashMap<String,Integer> mOps;
};

}
#endif
