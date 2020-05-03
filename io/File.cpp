#include <limits.h>
#include <dirent.h>
#include <string.h>

#include "Error.hpp"


#include "File.hpp"

namespace obotcha {

const String _File::gPathSeparator = createString("/");

const int _File::FileAlreadyExist = 0;

const int _File::ReadOnly = O_RDONLY;
const int _File::WriteOnly = O_WRONLY;
const int _File::ReadWriteOnly = O_RDWR;
const int _File::Create = O_CREAT;
const int _File::Excl = O_EXCL;
const int _File::Noctty = O_NOCTTY;
const int _File::Trunc = O_TRUNC;
const int _File::Append = O_APPEND;
const int _File::NonBlock = O_NONBLOCK;
const int _File::NDelay = O_NDELAY;
const int _File::Sync = O_SYNC;
const int _File::NoFollow = O_NOFOLLOW;
const int _File::Directory = O_DIRECTORY;

const mode_t _File::IRWXU = S_IRWXU;
const mode_t _File::IRUSR = S_IRUSR;
const mode_t _File::IWUSR = S_IWUSR;
const mode_t _File::IXUSR = S_IXUSR;
const mode_t _File::IRWXG = S_IRWXG;
const mode_t _File::IRGRP = S_IRGRP;
const mode_t _File::IWGRP = S_IWGRP;
const mode_t _File::IXGRP = S_IXGRP;
const mode_t _File::IRWXO = S_IRWXO;
const mode_t _File::IROTH = S_IROTH;
const mode_t _File::IWOTH = S_IWOTH;
const mode_t _File::IXOTH = S_IXOTH;

_File::_File(const char * s) {
    mPath = createString(s);
    updateFileInfo();
}


_File::_File(String path) {
    mPath = path;
    updateFileInfo();
}

_File::_File() {
    mPath="";
    updateFileInfo();
}

String _File::getName() {
    ArrayList<String> splits = mPath->split(gPathSeparator);
    if(splits == nullptr) {
        return mPath;
    }

    int size = splits->size();
    if(size > 0) {
        return splits->get(size - 1);
    }

    return nullptr;
}

String _File::getAbsolutePath() {
    char abs_path_buff[PATH_MAX];
    char *p =  realpath(mPath->toChars(), abs_path_buff);
    if(p == nullptr) {
        return nullptr;
    }

    return createString(p);
}

bool _File::canRead() {
   if (geteuid() == 0){
       return true;     
    }
   
    if (mFileInfo.st_uid == geteuid()) {
        return (mFileInfo.st_mode & S_IRUSR) != 0;     
    } else if(mFileInfo.st_gid == getegid()) {
        return (mFileInfo.st_mode & S_IRGRP) != 0;     
    } else {
        return (mFileInfo.st_mode & S_IROTH) != 0;
    }

    return false;
}

bool _File::canWrite() {
    if (geteuid() == 0){
       return true;     
    }
   
    if (mFileInfo.st_uid == geteuid()) {
        return (mFileInfo.st_mode & S_IWUSR) != 0;     
    } else if(mFileInfo.st_gid == getegid()) {
        return (mFileInfo.st_mode & S_IWGRP) != 0;     
    } else {
        return (mFileInfo.st_mode & S_IWOTH) != 0;
    }

    return false;
}

bool _File::canExecute() {
    //root may have no permission to execute
    if (mFileInfo.st_uid == geteuid()|| geteuid() == 0) {
        return (mFileInfo.st_mode & S_IXUSR) != 0;     
    } else if(mFileInfo.st_gid == getegid()) {
        return (mFileInfo.st_mode & S_IXGRP) != 0;     
    } else {
        return (mFileInfo.st_mode & S_IXOTH) != 0;
    }

    return false;
}

bool _File::exists() {
    return (mExist == FileAlreadyExist);
}

bool _File::isDirectory() {
    return S_ISDIR(mFileInfo.st_mode);
}

bool _File::isFile() {
    return !S_ISDIR(mFileInfo.st_mode);
}

bool _File::isHidden() {
    return false;
}

long _File::lastModified() {
    return false;
}

long _File::length() {
    updateFileInfo();
    return mFileInfo.st_size;
}

int _File::createNewFile(int flag,mode_t mode) {
    if(mExist == FileAlreadyExist) {
        return CreateFailAlreadyExist;
    }

    mode_t m = umask(000);
    int fd = ::open(mPath->toChars(),flag,mode);
    umask(m);

    updateFileInfo();

    if(mExist != FileAlreadyExist) {
        return CreateFail;
    }
    close(fd);
    return CreateSuccess;
}


bool _File::removeAll() {
    if(mExist != FileAlreadyExist) {
        return true;
    }
    
    if(isFile()) {
        //delete file;
        remove(mPath->toChars());
    } else {
        //delete dir
        deleteDir(this);
    }

    updateFileInfo();

    return true;
}

void _File::deleteDir(File f) {
    if(f->isFile()) {
        remove(f->getAbsolutePath()->toChars());
    } else {
        ArrayList<File> files = f->listFiles();

        int size = files->size();
        for(int i = 0;i < size;i++) {
            deleteDir(files->get(i));
        }
        //delete dir
        remove(f->getAbsolutePath()->toChars());
    }
}

ArrayList<String> _File::list() {
    DIR *dir;
    struct dirent *ptr;
    //char base[PATH_MAX];

    if(isFile()) {
        return nullptr;
    }

    ArrayList<String> files = createArrayList<String>();

    if((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name,".")==0 
           || strcmp(ptr->d_name,"..")==0) {
            continue;
        }///current dir OR parrent dir
        
        files->add(createString(ptr->d_name));
    }

    closedir(dir);

    return files;
}

ArrayList<File> _File::listFiles() {
    DIR *dir;
    struct dirent *ptr;
    //char base[PATH_MAX];

    if(isFile()) {
        return nullptr;
    }

    ArrayList<File> files = createArrayList<File>();

    if((dir = opendir(mPath->toChars())) == nullptr) {
        return nullptr;
    }

    while ((ptr = readdir(dir)) != NULL) {
        if(strcmp(ptr->d_name,".")==0 
           || strcmp(ptr->d_name,"..")==0) {
            continue;
        }///current dir OR parrent dir
        
        String path = createString(mPath);
        path->append(gPathSeparator);
        path->append(ptr->d_name);

        File file = createFile(path);
        files->add(file);
    }

    closedir(dir);
    
    return files;
}

bool _File::createDir() {
    mkdir(mPath->toChars(),0755);
    return true;
}

bool _File::createDirs() {
    ArrayList<String> splits = mPath->split(gPathSeparator);
    if(splits == nullptr) {
        return false;
    }
    
    int size = splits->size();
    //String path = splits->remove(0);

    String path = createString();
    for(int i = 0;i < size;i++) {
        //create...
        String p = splits->get(i);

        if(i != 0) {
            path->append(gPathSeparator);
        }

        path->append(p);

        if(p->equals(".") 
            || p->equals("..")) {
            continue;
        }

        if(access(path->toChars(),R_OK) != 0) {
            if(mkdir(path->toChars(),0755)==-1){
                //return false;
            }
        }        
    }

    return true;
}

int _File::rename(String name) {
    int index = name->lastIndexOf("/");
    String dir = name->subString(0,index);
    String newPath = dir->append(name);
    return ::rename(mPath->toChars(),newPath->toChars());
}

int _File::setReadOnly() {
    return setMode(S_IRUSR|S_IRGRP|S_IROTH);
}

int _File::setWriteOnly() {
    return setMode(S_IWUSR|S_IWGRP|S_IWOTH);
}

int _File::setExecuteOnly() {
    return setMode(S_IXUSR|S_IXGRP|S_IXOTH);
}

int _File::setWritable() {
    mode_t mode = mFileInfo.st_mode;
    mode |= S_IWUSR;
    mode |= S_IWGRP;
    mode |= S_IWOTH;

    if(setMode(mode) == 0) {
        mFileInfo.st_mode = mode;
        return 0;
    }

    return -InvalidStatus;
}

int _File::setReadable() {
    mode_t mode = mFileInfo.st_mode;
    mode |= S_IRUSR;
    mode |= S_IRGRP;
    mode |= S_IROTH;

     if(setMode(mode) == 0) {
        mFileInfo.st_mode = mode;
        return 0;
    }

    return -InvalidStatus;
}

int _File::setExecutable() {
    mode_t mode = mFileInfo.st_mode;
    mode |= S_IXUSR;
    mode |= S_IXGRP;
    mode |= S_IXOTH;

     if(setMode(mode) == 0) {
        mFileInfo.st_mode = mode;
        return 0;
    }

    return -InvalidStatus;
}

bool _File::exists(String path) {
    return (access(path->toChars(),F_OK) == 0);
}

void _File::updateFileInfo() {
    memset(&mFileInfo,0,sizeof(struct stat));
    String path = getAbsolutePath();
    if(path == nullptr) {
        mExist = -1;
        return;
    }

    mExist = stat(getAbsolutePath()->toChars(),&mFileInfo);
}

mode_t _File::getMode() {
    if(mExist != FileAlreadyExist ) {
        return  -1;
    }

    return mFileInfo.st_mode;
}

int _File::setMode(mode_t mode) {
    mode_t mask = umask(0);
    if(chmod(mPath->toChars(),mode) == 0) {
        mFileInfo.st_mode = mode;
        umask(mask);
        return 0;
    }

    umask(mask);
    return -InvalidStatus;
}

_File::~_File() {

}

}