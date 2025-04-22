/**
 * @file File.cpp
 * @brief A representation of file and directory pathnames..
 * @details none
 * @mainpage none
 * @author sunli.wang
 * @email wang_sun_1983@yahoo.co.jp
 * @version 0.0.1
 * @date 2024-01-03
 * @license none
 * @reference
 * https://en.cppreference.com/w/cpp/filesystem
 */
#include <dirent.h>
#include <unistd.h> 
#include <sys/stat.h>

#include "File.hpp"
#include "Inspect.hpp"
#include "Log.hpp"

namespace obotcha {

const String _File::kSeparator = String::New("/");
const String _File::kSuffix = String::New(".");

#define UPDATE_FILE_INFO(ERR) \
    struct stat info = {0}; \
    Inspect(updateFileInfo(&info) != 0,ERR)

_File::_File(const char *path):_File(String::New(path)) {
}

_File::_File(String path) {
    mPath = path->contains("/")?path:String::New("./")->append(path);
}

_File::_File() {
    mPath = String::New("");
}

String _File::getName() const {
    ArrayList<String> names = mPath->split("/");
    int size = names->size();
    for(int i = size - 1;i >= 0;i--) {
        auto name = names->get(i);
        if(name != nullptr && name->size() != 0) {
            return name;
        }
    }

    //path like "/////" will return null,
    //but it is the rootpath.add a traps,haha
    if(mPath->contains("/")) {
        return String::New("/");
    }

    return nullptr;
}

String _File::getSuffix() const {
    auto index = mPath->lastIndexOf(".");
    if(index != -1 && index != mPath->size() - 1) {
        return mPath->subString(index + 1,mPath->size() - index - 1);
    }

    return nullptr;
}

String _File::getNameWithNoSuffix() const {
    String name = getName();
    int index = name->size() - 1;
    const char *pname = name->toChars();
    for(; index > 0;index--) {
        if(pname[index] == '.') {
            break;
        }
    }

    if(index > 0) {
        return name->subString(0,index);
    }
    return name;
}

String _File::getAbsolutePath() const {
    char abs_path_buff[PATH_MAX] = {0};
    char *p = realpath(mPath->toChars(), abs_path_buff);
    return (p == nullptr)?nullptr:String::New((const char *)p);
}

bool _File::canRead()const {
    return access(mPath->toChars(),R_OK) == 0;
}

bool _File::canWrite() const {
    return access(mPath->toChars(),W_OK) == 0;
}

bool _File::canExecute() const {
    return access(mPath->toChars(),X_OK) == 0;
}

bool _File::exists() const {
    String path = getAbsolutePath();
    return (path != nullptr) &&
        (access(path->toChars(), F_OK) == 0);
}

bool _File::isDirectory() const {
    //std::filesystem::is_directory(folderPath);
    UPDATE_FILE_INFO(false);
    return S_ISDIR(info.st_mode);
}

bool _File::isFile() const {
    UPDATE_FILE_INFO(false);
    return !S_ISDIR(info.st_mode);
}

long _File::lastModified() const {
    UPDATE_FILE_INFO(-1)
    return info.st_mtim.tv_sec*1000 + info.st_mtim.tv_nsec/1000000;
}

long _File::lastAccess() const {
    UPDATE_FILE_INFO(-1)
    return info.st_atim.tv_sec*1000 + info.st_atim.tv_nsec/1000000;
}

long _File::lastStatusChanged() const {
    UPDATE_FILE_INFO(-1)    
    return info.st_ctim.tv_sec*1000 + info.st_ctim.tv_nsec/1000000;
}

long _File::length() const {
    UPDATE_FILE_INFO(-1)
    return info.st_size;
}

int _File::createNewFile(int flag, mode_t mode) const {
    mode_t m = umask(000);
    flag |= O_CREAT;
    int fd = ::open(mPath->toChars(), flag, mode);
    umask(m);

    Inspect(fd < 0,-1)
    return close(fd);
}

FileDescriptor _File::Open(String path,int flags,int mode) {
    File file = File::New(path);
    return file->open(flags,mode);
}

FileDescriptor _File::open(int flags,int mode) const {
    int fd = ::open(mPath->toChars(),flags,mode);
    return fd >= 0?FileDescriptor::New(fd):nullptr;
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

ArrayList<String> _File::list() const {
    DIR *dir;
    struct dirent *ptr;
    
    Inspect(isFile(),nullptr)

    ArrayList<String> files = ArrayList<String>::New();

    if ((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } /// current dir OR parrent dir

        files->add(String::New(ptr->d_name));
    }
    closedir(dir);
    return files;
}

ArrayList<File> _File::listFiles() {
    DIR *dir;
    struct dirent *ptr;
    
    Inspect(isFile(),nullptr)

    ArrayList<File> files = ArrayList<File>::New();

    if ((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        } /// current dir OR parrent dir

        String path = String::New(mPath)->append(kSeparator)->append(ptr->d_name);
        File file = File::New(path);
        files->add(file);
    }

    closedir(dir);
    return files;
}

bool _File::createDir() const {
  return (mkdir(mPath->toChars(), 0755) == 0);
}

bool _File::createDirs() const {
    ArrayList<String> splits = mPath->split(kSeparator);
    Inspect(splits == nullptr,false)

    int size = splits->size();
    String path = String::New();
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
    auto index = mPath->lastIndexOf("/");
    auto newPath = mPath->subString(0, index+1)->append(name);
    int result = ::rename(mPath->toChars(), newPath->toChars());
    if(result == 0) {
        mPath = newPath;
    }

    return result;
}

int _File::setReadOnly() const {
    return setMode(S_IRUSR | S_IRGRP | S_IROTH);
}

int _File::setWriteOnly() const {
    return setMode(S_IWUSR | S_IWGRP | S_IWOTH);
}

int _File::setExecuteOnly() const {
    return setMode(S_IXUSR | S_IXGRP | S_IXOTH);
}

int _File::setWritable() const {
    UPDATE_FILE_INFO(-1)

    mode_t mode = info.st_mode;
    mode |= S_IWUSR;
    mode |= S_IWGRP;
    mode |= S_IWOTH;

    return setMode(mode);
}

int _File::setReadable() const {
    UPDATE_FILE_INFO(-1)

    mode_t mode = info.st_mode;
    mode |= S_IRUSR;
    mode |= S_IRGRP;
    mode |= S_IROTH;

    return setMode(mode);
}

int _File::setExecutable() const {
    UPDATE_FILE_INFO(-1)

    mode_t mode = info.st_mode;
    mode |= S_IXUSR;
    mode |= S_IXGRP;
    mode |= S_IXOTH;

    return setMode(mode);
}

bool _File::Exists(String path) {
    return access(path->toChars(), F_OK) == 0;
}

int _File::updateFileInfo(struct stat *info) const {
    memset(info, 0, sizeof(struct stat));
    String path = getAbsolutePath();
    Inspect(path == nullptr,-1)

    return stat(path->toChars(), info);
}

 bool _File::deleteDir(sp<_File> f) {
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
    return true;
 }

mode_t _File::getMode() const {
    UPDATE_FILE_INFO(-1)
    return info.st_mode;
}

int _File::setMode(mode_t mode) const {
    mode_t mask = umask(0);
    auto ret = chmod(mPath->toChars(), mode);
    umask(mask);
    return (ret == 0)?0:-1;
}

} // namespace obotcha
