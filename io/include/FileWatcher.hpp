#ifndef __OBOTCHA_FILE_OBSERVER_HPP__
#define __OBOTCHA_FILE_OBSERVER_HPP__

#include <sys/inotify.h>

#include "Object.hpp"
#include "HashMap.hpp"
#include "Mutex.hpp"
#include "String.hpp"
#include "Thread.hpp"
#include "EPollObserver.hpp"
#include "OStdApply.hpp"

namespace obotcha {

class _FileWatcher;

DECLARE_CLASS(FileUpdateListener) {
public:
    friend class _FileWatcher;
    virtual void onFileUpdate(String filepath, int op,int origid,int currentid) = 0;

    void setPath(String p);
    String getPath();

    void setOperations(int);
    int getOperations();
private:
    String mPath;
    int mOperations;
};

template <class Function, class... Args>
class _LambdaFileUpdateListener : public _FileUpdateListener {
public:
    _LambdaFileUpdateListener(Function f, Args... args)
        : _FileUpdateListener(), func(f), _arguments(std::make_tuple(args...)) {}

    void onFileUpdate(String filepath, int op,int origid,int currentid) override {
        auto param = std::tuple_cat(std::make_tuple(filepath,op,origid,currentid), _arguments);
        ostd::apply(func,param);
    }

    ~_LambdaFileUpdateListener() override = default;

private:
    std::tuple<Args...> _arguments;
    Function func;
};

template <typename Callfunc, typename... Args>
sp<_FileUpdateListener> createFileUpdateListenerLambda(Callfunc f, Args... args) {
    _FileUpdateListener *r = new _LambdaFileUpdateListener<Callfunc, Args...>(f,args...);
    return AutoClone(r);
}

DECLARE_CLASS(FileWatcher) IMPLEMENTS(EPollListener) {
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

    template <typename T>
    int startWatch(String filepath, int op, sp<T> observer) {
        AutoLock lock(mutex);
        int id = inotify_add_watch(notifyFd, filepath->toChars(), op);
        observer->setPath(filepath);
        observer->setOperations(op);
        mNodes->put(id,observer);
        return id;
    }

    template <class Function, class... Args>
    int startWatch(String filepath, int op,Function f, Args... args) {
        auto listener = createFileUpdateListenerLambda(f, args...);
        return startWatch(filepath,op,listener);
    }

    int stopWatch(int id);
    void close();
    st(IO)::Epoll::Result onEvent(int fd, uint32_t events);

private:
    int notifyFd;
    Mutex mutex = Mutex::New();
    HashMap<int, FileUpdateListener> mNodes = HashMap<int, FileUpdateListener>::New();

    EPollObserver mObserver;
};


} // namespace obotcha
#endif
