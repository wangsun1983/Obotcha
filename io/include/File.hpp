#ifndef __OBOTCHA_FILE_HPP__
#define __OBOTCHA_FILE_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>
#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>


#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(File) {
public:
    _File(const char *);
    
    _File(String path);

    _File();

    String getName();

    String getSuffix();

    String getNameWithNoSuffix();

    String getAbsolutePath();

    bool canRead();

    bool canWrite();

    bool canExecute();

    bool exists();

    bool isDirectory();

    bool isFile();

    bool isHidden();

    long lastModified();

    long length();

     int createNewFile(int flags=O_CREAT, mode_t mode=0666);

    bool removeAll();

    ArrayList<String> list();

    ArrayList<File> listFiles();

    bool createDir();

    bool createDirs();

    int rename(String name);

    int setReadOnly();

    int setWriteOnly();

    int setExecuteOnly();

    int setWritable();

    int setReadable();

    int setExecutable();

    int setMode(mode_t);

    mode_t getMode();

    ~_File();
    
    static const String gPathSeparator;
    static const String gPathSuffix;
    
    static bool exists(String);
    
    enum OpenType {
        ReadOnly = O_RDONLY,
        WriteOnly = O_WRONLY,
        ReadWriteOnly = O_RDWR,
        Create = O_CREAT,
        Excl = O_EXCL,
        Noctty = O_NOCTTY,
        Trunc = O_TRUNC,
        Append = O_APPEND,
        NonBlock = O_NONBLOCK,
        NDelay = O_NDELAY,
        Sync = O_SYNC,
        NoFollow = O_NOFOLLOW,
        Directory = O_DIRECTORY,
    };

    enum FileMode {
        IRWXU = S_IRWXU,
        IRUSR = S_IRUSR,
        IWUSR = S_IWUSR,
        IXUSR = S_IXUSR,
        IRWXG = S_IRWXG,
        IRGRP = S_IRGRP,
        IWGRP = S_IWGRP,
        IXGRP = S_IXGRP,
        IRWXO = S_IRWXO,
        IROTH = S_IROTH,
        IWOTH = S_IWOTH,
        IXOTH = S_IXOTH,
    };

private:

    int updateFileInfo(struct stat *info);

    void deleteDir(File f);

    int mFlags;

    mode_t mMode;
    
    String mPath;
};

}
#endif
