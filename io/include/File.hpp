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

    enum FileCreateResult {
        CreateSuccess = 0,
        CreateFailAlreadyExist,
        CreateFail
    };

    _File(const char *);
    
    _File(String path);

    _File();

    String getName();

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
    
    static bool exists(String);

    static const int ReadOnly;
    static const int WriteOnly;
    static const int ReadWriteOnly;
    static const int Create;
    static const int Excl;
    static const int Noctty;
    static const int Trunc;
    static const int Append;
    static const int NonBlock;
    static const int NDelay;
    static const int Sync;
    static const int NoFollow;
    static const int Directory;

    static const mode_t IRWXU;
    static const mode_t IRUSR;
    static const mode_t IWUSR;
    static const mode_t IXUSR;
    static const mode_t IRWXG;
    static const mode_t IRGRP;
    static const mode_t IWGRP;
    static const mode_t IXGRP;
    static const mode_t IRWXO;
    static const mode_t IROTH;
    static const mode_t IWOTH;
    static const mode_t IXOTH;

    static const int FileAlreadyExist;

private:

    void updateFileInfo();

    void deleteDir(File f);

    int mFlags;

    mode_t mMode;
    
    String mPath;

    struct stat mFileInfo;

    int mExist;
};

}
#endif
