#include "File.hpp"

int File::sFileStatusExit = 0;
String File::gPathSeparator = new String("//");

_File::_File(String path) {
    mPath = path;
    mFileInfo = nullptr;
    mExist = -1;
    fileStream = nullptr;
}

String _File::getName() {
    
}

String _File::getAbsolutePath() {

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
    if(mFileInfo == nullptr) {
        updateFileInfo();
    }

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

    return S_ISREG(mFileInfo->st_mode);
}

bool _File::isHidden() {

}

long _File::lastModified() {

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

    fileStream = new std::ofstream(mPath->toChars());
    updateFileInfo();

    if(mExist != sFileStatusExit) {
        return CreateFail;
    }

    return CreateSuccess;
    
}

bool _File::remove() {

}

ArrayList<String> _File::list() {

}

ArrayList<File> _File::listFiles() {

}

bool _File::mkdir() {

}

bool _File::mkdirs() {
    ArrayList<String> splits = createArrayList<String>();
    mPath->splits(gPathSeparator,splits);

    if(splits == 0) {
        return false;
    }

    int size = splits->size();
    String path = splits->remove(0);

    for(int i = 0;i < size;i++) {
        //create...
    }

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

long _File::getTotalSpace() {

}

long _File::getFreeSpace() {

}

long _File::getUsableSpace() {

}

void _File::updateFileInfo() {
    if(mFileInfo != nullptr) {
        free(mFileInfo);
    }

    mFileInfo = (struct stat *)malloc(sizeof(struct stat));
    mExist = stat(mPath->toChars(),mFileInfo);
}

bool _File::createDirectory(String str) {

}

_File::~_File() {
    if(fileStream != nullptr) {
        fileStream->close();
    }
}