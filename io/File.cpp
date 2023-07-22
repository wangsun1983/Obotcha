#include <dirent.h>

#include "File.hpp"
#include "Inspect.hpp"
#include "Log.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

const String _File::kSeparator = createString("/");
const String _File::kSuffix = createString(".");

#define UPDATE_FILE_INFO(ERR) \
    struct stat info = {0}; \
    Inspect(updateFileInfo(&info) != 0,ERR)

_File::_File(const char *path):_File(createString(path)) {
}

_File::_File(String path) {
    mPath = path->contains(kSeparator)?path:createString("./")->append(path);
}

_File::_File() {
    mPath = createString("");
}

String _File::getName() {
    int size = mPath->size();
    Inspect(size == 1,mPath)

    int start = size - 1;
    const char *data = mPath->toChars();
    for (; start >= 0; start--) {
        if (data[start] == '/' && start != size - 1) {
            break;
        }
    }
    Inspect(start == -1,mPath)

    int len = 0;
    if(data[size - 1] == '/') {
        len = size - start - 1 - 1; //remove '/',it is a directory
    } else {
        len = size - start - 1;
    }
    return mPath->subString(start + 1,len);
}

String _File::getSuffix() {
    int index = mPath->lastIndexOf(".");
    if(index != -1 && index != mPath->size() - 1) {
        return mPath->subString(index + 1,mPath->size() - index - 1);
    }

    return nullptr;
}

String _File::getNameWithNoSuffix() {
    String name = getName();
    ArrayList<String> names = name->split(".");
    if(names == nullptr || names->size() < 2) {
        return name;
    }

    String result = createString();
    int size = names->size() - 1; //do not append last
    for(int i = 0 ; i < size;i++) {
        result = result->append(names->get(i),".");
    }

    return result->subString(0,result->size() - 1);
}

String _File::getAbsolutePath() {
    char abs_path_buff[PATH_MAX] = {0};
    char *p = realpath(mPath->toChars(), abs_path_buff);
    return (p == nullptr)?nullptr:createString((const char *)p);
}

bool _File::canRead() {
    Inspect(geteuid() == 0,true)

    UPDATE_FILE_INFO(false);

    if (info.st_uid == geteuid()) {
        return (info.st_mode & S_IRUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IRGRP) != 0;
    } 
    
    return (info.st_mode & S_IROTH) != 0;
}

bool _File::canWrite() {
    Inspect(geteuid() == 0,true)

    UPDATE_FILE_INFO(false);
    
    if (info.st_uid == geteuid()) {
        return (info.st_mode & S_IWUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IWGRP) != 0;
    } 
    
    return (info.st_mode & S_IWOTH) != 0;
}

bool _File::canExecute() {
    UPDATE_FILE_INFO(false);
    
    // root may have no permission to execute
    if (info.st_uid == geteuid() || geteuid() == 0) {
        return (info.st_mode & S_IXUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IXGRP) != 0;
    } 
    
    return (info.st_mode & S_IXOTH) != 0;
}

bool _File::exists() {
    String path = getAbsolutePath();
    return (path != nullptr) &&
        (access(path->toChars(), F_OK) == 0);
}

bool _File::isDirectory() {
    UPDATE_FILE_INFO(false);
    return S_ISDIR(info.st_mode);
}

bool _File::isFile() {
    UPDATE_FILE_INFO(false);
    return !S_ISDIR(info.st_mode);
}

long _File::lastModified() {
    UPDATE_FILE_INFO(-1);
    return info.st_mtim.tv_sec*1000 + info.st_mtim.tv_nsec/1000000;
}

long _File::lastAccess() {
    UPDATE_FILE_INFO(-1);
    return info.st_atim.tv_sec*1000 + info.st_atim.tv_nsec/1000000;
}

long _File::lastStatusChanged() {
    UPDATE_FILE_INFO(-1);    
    return info.st_ctim.tv_sec*1000 + info.st_ctim.tv_nsec/1000000;
}

long _File::length() {
    UPDATE_FILE_INFO(-1);
    return info.st_size;
}

int _File::createNewFile(int flag, mode_t mode) {
    mode_t m = umask(000);
    flag |= O_CREAT;
    int fd = ::open(mPath->toChars(), flag, mode);
    umask(m);

    Inspect(fd < 0,-1)
    return close(fd);
}

FileDescriptor _File::open(String path,int flags,int mode) {
    File file = createFile(path);
    return file->open(flags,mode);
}

FileDescriptor _File::open(int flags,int mode) {
    int fd = ::open(mPath->toChars(),flags,mode);
    return fd >= 0?createFileDescriptor(fd):nullptr;
}

bool _File::removeAll() {
    Inspect(!exists(),true)

    if (isFile()) {
        remove(mPath->toChars());
    } else {
        deleteDir(this);
    }
    return true;
}

void _File::deleteDir(File f) {
    if (f->isFile()) {
        remove(f->getAbsolutePath()->toChars());
    } else {
        ArrayList<File> files = f->listFiles();

        int size = files->size();
        for (int i = 0; i < size; i++) {
            deleteDir(files->get(i));
        }
        // delete dir
        remove(f->getAbsolutePath()->toChars());
    }
}

ArrayList<String> _File::list() {
    DIR *dir;
    struct dirent *ptr;
    
    Inspect(isFile(),nullptr)

    ArrayList<String> files = createArrayList<String>();

    if ((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } /// current dir OR parrent dir

        files->add(createString(ptr->d_name));
    }
    closedir(dir);
    return files;
}

ArrayList<File> _File::listFiles() {
    DIR *dir;
    struct dirent *ptr;
    
    Inspect(isFile(),nullptr)

    ArrayList<File> files = createArrayList<File>();

    if ((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } /// current dir OR parrent dir

        String path = createString(mPath)->append(kSeparator)->append(ptr->d_name);
        File file = createFile(path);
        files->add(file);
    }

    closedir(dir);
    return files;
}

bool _File::createDir() {
  return (mkdir(mPath->toChars(), 0755) == 0);
}

bool _File::createDirs() {
    ArrayList<String> splits = mPath->split(kSeparator);
    Inspect(splits == nullptr,false)

    int size = splits->size();
    String path = createString();
    for (int i = 0; i < size; i++) {
        // create...
        String p = splits->get(i);

        if (i != 0) {
            path = path->append(kSeparator);
        }

        path = path->append(p);
        if (p->sameAs(".") || p->sameAs("..")) {
            continue;
        }

        if (access(path->toChars(), R_OK) != 0 
            && mkdir(path->toChars(), 0755) == -1) {
                LOG(ERROR) << "create " << path->toChars() << " failed";
        }
    }

    return true;
}

int _File::rename(String name) {
    int index = mPath->lastIndexOf("/");
    auto newPath = mPath->subString(0, index+1)->append(name);
    int result = ::rename(mPath->toChars(), newPath->toChars());
    if(result == 0) {
        mPath = newPath;
    }

    return result;
}

int _File::setReadOnly() {
    return setMode(S_IRUSR | S_IRGRP | S_IROTH);
}

int _File::setWriteOnly() {
    return setMode(S_IWUSR | S_IWGRP | S_IWOTH);
}

int _File::setExecuteOnly() {
    return setMode(S_IXUSR | S_IXGRP | S_IXOTH);
}

int _File::setWritable() {
    UPDATE_FILE_INFO(-1);

    mode_t mode = info.st_mode;
    mode |= S_IWUSR;
    mode |= S_IWGRP;
    mode |= S_IWOTH;

    return setMode(mode);
}

int _File::setReadable() {
    UPDATE_FILE_INFO(-1);

    mode_t mode = info.st_mode;
    mode |= S_IRUSR;
    mode |= S_IRGRP;
    mode |= S_IROTH;

    return setMode(mode);
}

int _File::setExecutable() {
    UPDATE_FILE_INFO(-1);

    mode_t mode = info.st_mode;
    mode |= S_IXUSR;
    mode |= S_IXGRP;
    mode |= S_IXOTH;

    return setMode(mode);
}

bool _File::exists(String path) {
    return access(path->toChars(), F_OK) == 0;
}

int _File::updateFileInfo(struct stat *info) {
    memset(info, 0, sizeof(struct stat));
    String path = getAbsolutePath();
    Inspect(path == nullptr,-1)

    return stat(path->toChars(), info);
}

mode_t _File::getMode() {
    UPDATE_FILE_INFO(-1);
    return info.st_mode;
}

int _File::setMode(mode_t mode) {
    mode_t mask = umask(0);
    auto ret = chmod(mPath->toChars(), mode);
    umask(mask);
    return (ret == 0)?0:-1;
}

//_File::~_File() {
    //do nothing
//}

} // namespace obotcha
