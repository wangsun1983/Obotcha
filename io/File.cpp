#include <dirent.h>
#include <limits.h>
#include <string.h>

#include "Error.hpp"
#include "File.hpp"
#include "Log.hpp"
#include "System.hpp"


namespace obotcha {

const String _File::Separator = createString("/");
const String _File::Suffix = createString(".");

_File::_File(const char *s):_File(createString(s)) {
}

_File::_File(String path) {
    mPath = path;
}

_File::_File() {
    mPath = createString("");
}

String _File::getName() {
    int size = mPath->size();
    int start = size - 1;
    const char *data = mPath->toChars();
    if(size == 1) {
        return mPath;
    }

    for (; start >= 0; start--) {
        if (data[start] == '/' && start != size - 1) {
            break;
        }
    }

    if(start == -1) {
        return mPath;
    }

    int len = 0;
    if(data[size - 1] == '/') {
        len = mPath->size() - start - 1 - 1; //remove '/',it is a directory
    } else {
        len = mPath->size() - start - 1;
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
    int size = mPath->size();
    int index = size - 1;
    const char *data = mPath->toChars();

    int end = size;
    int start = 0;
    for(;index >= 0;index--) {
        if (data[index] == '.' && end == size) {
            end = index;
        }

        if (data[index] == '/') {
            return mPath->subString(index + 1,end - index - 1);
        }
    }

    if(end != 0) {
        return mPath->subString(0,end - start);
    }

    return mPath;
}

String _File::getAbsolutePath() {
    char abs_path_buff[PATH_MAX] = {0};
    char *p = realpath(mPath->toChars(), abs_path_buff);
    return (p == nullptr)?nullptr:createString((const char *)p);
}

bool _File::canRead() {
    if (geteuid() == 0) {
        return true;
    }

    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return false;
    }

    if (info.st_uid == geteuid()) {
        return (info.st_mode & S_IRUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IRGRP) != 0;
    } else {
        return (info.st_mode & S_IROTH) != 0;
    }

    return false;
}

bool _File::canWrite() {
    if (geteuid() == 0) {
        return true;
    }

    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return false;
    }

    if (info.st_uid == geteuid()) {
        return (info.st_mode & S_IWUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IWGRP) != 0;
    } else {
        return (info.st_mode & S_IWOTH) != 0;
    }

    return false;
}

bool _File::canExecute() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return false;
    }

    // root may have no permission to execute
    if (info.st_uid == geteuid() || geteuid() == 0) {
        return (info.st_mode & S_IXUSR) != 0;
    } else if (info.st_gid == getegid()) {
        return (info.st_mode & S_IXGRP) != 0;
    } else {
        return (info.st_mode & S_IXOTH) != 0;
    }

    return false;
}

bool _File::exists() {
    String path = getAbsolutePath();
    if (path == nullptr) {
        return false;
    }

    return (access(path->toChars(), F_OK) == 0);
}

bool _File::isDirectory() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return false;
    }

    return S_ISDIR(info.st_mode);
}

bool _File::isFile() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return false;
    }

    return !S_ISDIR(info.st_mode);
}

long _File::lastModified() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    return info.st_mtim.tv_sec*1000 + info.st_mtim.tv_nsec/1000000;
}

long _File::lastAccess() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    return info.st_atim.tv_sec*1000 + info.st_atim.tv_nsec/1000000;
}

long _File::lastStatusChanged() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    return info.st_ctim.tv_sec*1000 + info.st_ctim.tv_nsec/1000000;
}

long _File::length() {
    struct stat info = {0};
    updateFileInfo(&info);
    return info.st_size;
}

int _File::createNewFile(int flag, mode_t mode) {
    mode_t m = umask(000);
    flag |= O_CREAT;
    int fd = ::open(mPath->toChars(), flag, mode);
    umask(m);
    if (fd < 0) {
        return -1;
    }

    return close(fd);
}

bool _File::removeAll() {
    if (!exists()) {
        return true;
    }
    if (isFile()) {
        // delete file;
        remove(mPath->toChars());
    } else {
        // delete dir
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

    if (isFile()) {
        return nullptr;
    }

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
    // char base[PATH_MAX];

    if (isFile()) {
        return nullptr;
    }

    ArrayList<File> files = createArrayList<File>();

    if ((dir = opendir(mPath->toChars())) == NULL) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } /// current dir OR parrent dir

        String path =
            createString(mPath)->append(Separator)->append(ptr->d_name);

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
    ArrayList<String> splits = mPath->split(Separator);
    if (splits == nullptr) {
        return false;
    }

    int size = splits->size();
    String path = createString();
    for (int i = 0; i < size; i++) {
        // create...
        String p = splits->get(i);

        if (i != 0) {
            path = path->append(Separator);
        }

        path = path->append(p);
        if (p->equals(".") || p->equals("..")) {
            continue;
        }

        if (access(path->toChars(), R_OK) != 0) {
            if (mkdir(path->toChars(), 0755) == -1) {
                // return false;
                LOG(ERROR) << "create " << path->toChars() << " failed";
            }
        }
    }

    return true;
}

int _File::rename(String name) {
    int index = name->lastIndexOf("/");
    String dir = name->subString(0, index);
    String newPath = dir->append(name);
    return ::rename(mPath->toChars(), newPath->toChars());
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
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    mode_t mode = info.st_mode;
    mode |= S_IWUSR;
    mode |= S_IWGRP;
    mode |= S_IWOTH;

    return setMode(mode);
}

int _File::setReadable() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    mode_t mode = info.st_mode;
    mode |= S_IRUSR;
    mode |= S_IRGRP;
    mode |= S_IROTH;

    return setMode(mode);
}

int _File::setExecutable() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    mode_t mode = info.st_mode;
    mode |= S_IXUSR;
    mode |= S_IXGRP;
    mode |= S_IXOTH;

    return setMode(mode);
}

bool _File::exists(String path) {
    return (access(path->toChars(), F_OK) == 0);
}

int _File::updateFileInfo(struct stat *info) {
    memset(info, 0, sizeof(struct stat));
    String path = getAbsolutePath();
    if (path == nullptr) {
        return -1;
    }

    return stat(getAbsolutePath()->toChars(), info);
}

mode_t _File::getMode() {
    struct stat info = {0};
    if (updateFileInfo(&info) != 0) {
        return -1;
    }

    return info.st_mode;
}

int _File::setMode(mode_t mode) {
    mode_t mask = umask(0);
    if (chmod(mPath->toChars(), mode) == 0) {
        umask(mask);
        return 0;
    }

    umask(mask);
    return -1;
}

_File::~_File() {}

} // namespace obotcha
