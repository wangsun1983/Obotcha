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

class FileObserverType {
public:
    const static int Access = IN_ACCESS;                /* File was accessed.  */
    const static int Modify = IN_MODIFY;                /* File was modified.  */
    const static int Attrib = IN_ATTRIB;                /* Metadata changed.  */
    const static int CloseWrite = IN_CLOSE_WRITE;       /* Writtable file was closed.  */
    const static int CloseNoWrite = IN_CLOSE_NOWRITE;   /* Unwrittable file closed.  */
    const static int Close = IN_CLOSE;                  /* Close.  */
    const static int Open = IN_OPEN;                    /* File was opened.  */
    const static int MovedFrom = IN_MOVED_FROM;         /* File was moved from X.  */
    const static int MovedTo = IN_MOVED_TO;             /* File was moved to Y.  */
    const static int Move = IN_MOVE;                    /* Moves.  */
    const static int Create = IN_CREATE;                /* Subfile was created.  */
    const static int Delete = IN_DELETE;                /* Subfile was deleted.  */
    const static int DeleteSelf = IN_DELETE_SELF;       /* Self was deleted.  */
    const static int MoveSelf = IN_MOVE_SELF;           /* Self was moved.  */
    const static int UnMount = IN_UNMOUNT;              /* Backing fs was unmounted.  */
    const static int OverFlow = IN_Q_OVERFLOW;          /* Event queued overflowed.  */
    const static int Ignored = IN_IGNORED;              /* File was ignored.  */

    const static int Full = Access|Modify|Attrib|CloseWrite
                            |CloseNoWrite|Close|Open|MovedFrom
                            |MovedTo|Move|Create|Delete
                            |DeleteSelf|MoveSelf|UnMount|OverFlow
                            |Ignored;

    const static int EventNum = 17;
};

DECLARE_SIMPLE_CLASS(FileObserver) {
public:
    virtual void onFileUpdate(String filepath,int op) = 0;
};

DECLARE_SIMPLE_CLASS(LocalFileObserverMonitor) {
public:
    int op;
    FileObserver mObserver;
};

DECLARE_SIMPLE_CLASS(FileWatcher) IMPLEMENTS(Thread) {
public:
    static sp<_FileWatcher> getInstance();
    
    int startWatch(String filepath,int op,sp<_FileObserver> observer);

    void stopWatch(int id,int op,FileObserver observer);

private:
    static Mutex mInitMutex;
    static sp<_FileWatcher> mInstance; 

    void run();

    int notifyFd;

    _FileWatcher();

    Mutex mutex;
    
    void openInotifyDev();

    int closeInotifyDev();

    void handleEvent(struct inotify_event *event);

    int readEvent();

    //HashMap<String,HashMap<int,ArrayList<FileObserver>>> mlisteners;
    HashMap<int,ArrayList<LocalFileObserverMonitor>> mListeners;
};

}
#endif
