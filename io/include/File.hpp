#ifndef __FILE_HPP__
#define __FILE_HPP__

#include <sys/stat.h>
#include <unistd.h>    
#include <sys/types.h>
#include <fstream>

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

    _File(String path);

    _File();

    void setPath(String path);

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

    int createNewFile();

    bool removeAll();

    ArrayList<String> list();

    ArrayList<File> listFiles();

    bool createDir();

    bool createDirs();

    bool rename(String name);

    bool setReadOnly();

    bool setWriteOnly();

    bool setExecuteOnly();

    bool setWritable();

    bool setReadable();

    bool setExecutable();

    ~_File();
    
    static const String gPathSeparator;

private:

    static int sFileStatusExit;

    String mPath;

    struct stat *mFileInfo;

    int mExist;

    void updateFileInfo();
        
    //std::ofstream *fileStream;

    void deleteDir(File f);

};

}
#endif
