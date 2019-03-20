#include <limits.h>
#include <dirent.h>
#include <string.h>

#include "File.hpp"

namespace obotcha {

int _File::sFileStatusExit = 0;

const String _File::gPathSeparator = createString("/");

_File::_File(String path) {
    mPath = path;
    mFileInfo = nullptr;
    mExist = -1;
    //fileStream = nullptr;
}

_File::_File() {
    mPath="";
    mFileInfo = nullptr;
    mExist = -1;
}

void _File::setPath(String path) {
    mPath = path;
    mFileInfo = nullptr;
    mExist = -1;
}

String _File::getName() {
    ArrayList<String> splits = createArrayList<String>();
    mPath->split(gPathSeparator,splits);

    int size = splits->size();

    if(size > 0) {
        return splits->get(size - 1);
    }

    return nullptr;
}

String _File::getAbsolutePath() {
    char abs_path_buff[PATH_MAX];
    realpath(mPath->toChars(), abs_path_buff);
    return createString(abs_path_buff);
}

bool _File::canRead() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    if (geteuid() == 0){
       return true;     
    }
   
    if (mFileInfo->st_uid == geteuid()) {
        return (mFileInfo->st_mode & S_IRUSR) != 0;     
    } else if(mFileInfo->st_gid == getegid()) {
        return (mFileInfo->st_mode & S_IRGRP) != 0;     
    } else {
        return (mFileInfo->st_mode & S_IROTH) != 0;
    }

    return false;
}

bool _File::canWrite() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    if (geteuid() == 0){
       return true;     
    }
   
    if (mFileInfo->st_uid == geteuid()) {
        return (mFileInfo->st_mode & S_IWUSR) != 0;     
    } else if(mFileInfo->st_gid == getegid()) {
        return (mFileInfo->st_mode & S_IWGRP) != 0;     
    } else {
        return (mFileInfo->st_mode & S_IWOTH) != 0;
    }

    return false;
}

bool _File::canExecute() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    //root may have no permission to execute
    if (mFileInfo->st_uid == geteuid()|| geteuid() == 0) {
        return (mFileInfo->st_mode & S_IXUSR) != 0;     
    } else if(mFileInfo->st_gid == getegid()) {
        return (mFileInfo->st_mode & S_IXGRP) != 0;     
    } else {
        return (mFileInfo->st_mode & S_IXOTH) != 0;
    }

    return false;
}

bool _File::exists() {
    //if(mFileInfo == nullptr) {
        updateFileInfo();
    //}

    return (mExist == sFileStatusExit);
}

bool _File::isDirectory() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    return S_ISDIR(mFileInfo->st_mode);
}

bool _File::isFile() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    return !S_ISDIR(mFileInfo->st_mode);
}

bool _File::isHidden() {
    return false;
}

long _File::lastModified() {
    return false;
}

long _File::length() {
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

    return mFileInfo->st_size;
}

int _File::createNewFile() {
    if(mFileInfo != nullptr) {
        updateFileInfo();
    }

    if(mExist == sFileStatusExit) {
        return CreateFailAlreadyExist;
    }

    //fileStream = new std::ofstream(mPath->toChars());
    std::ofstream stream(mPath->toChars());
    stream.close();

    updateFileInfo();

    if(mExist != sFileStatusExit) {
        return CreateFail;
    }

    return CreateSuccess;
    
}

bool _File::removeAll() {

    if(mFileInfo != nullptr) {
        updateFileInfo();
    }

    //printf("file remove all path is %s \n",mPath->toChars());
    if(mExist != sFileStatusExit) {
        return true;
    }
    //printf("file remove all 2 path is %s \n",mPath->toChars());

    if(isFile()) {
        //delete file;
        remove(mPath->toChars());
    } else {
        //delete dir
        deleteDir(this);
    }

    updateFileInfo();
}

void _File::deleteDir(File f) {
    if(f->isFile()) {
        remove(f->getAbsolutePath()->toChars());
    } else {
        ArrayList<File> files = f->listFiles();

        int size = files->size();
        for(int i = 0;i < size;i++) {
            printf("file name is %s \n",f->getAbsolutePath()->toChars());
            deleteDir(files->get(i));
        }
        //delete dir
        remove(f->getAbsolutePath()->toChars());
    }
}

ArrayList<String> _File::list() {
    DIR *dir;
    struct dirent *ptr;
    char base[PATH_MAX];

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
        printf("file is %s \n",ptr->d_name);
    }

    closedir(dir);

    return files;
}

ArrayList<File> _File::listFiles() {
    DIR *dir;
    struct dirent *ptr;
    char base[PATH_MAX];

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
        printf("file is %s \n",path->toChars());
    }

    closedir(dir);
    
    return files;
}

bool _File::createDir() {
    mkdir(mPath->toChars(),0755);
}

bool _File::createDirs() {
    ArrayList<String> splits = createArrayList<String>();
    mPath->split(gPathSeparator,splits);
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

bool _File::rename(String name) {

}

bool _File::setReadOnly() {

}

bool _File::setWriteOnly() {

}

bool _File::setExecuteOnly() {

}

bool _File::setWritable() {

}

bool _File::setReadable() {

}

bool _File::setExecutable() {

}

void _File::updateFileInfo() {
    if(mFileInfo == nullptr) {
        mFileInfo = (struct stat *)malloc(sizeof(struct stat));
    }

    memset(mFileInfo,0,sizeof(struct stat));

    mExist = stat(getAbsolutePath()->toChars(),mFileInfo);
    //printf("mExit is %d,path is %s \n",mExist,getAbsolutePath()->toChars());
}

_File::~_File() {
    if(mFileInfo != nullptr) {
        free(mFileInfo);
    }
}

}