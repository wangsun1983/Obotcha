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

DECLARE_SIMPLE_CLASS(File) {
public:

    enum FileCreateResult {
        CreateSuccess = 0,
        CreateFailAlreadyExist,
        CreateFail
    };

    _File(String path);

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

    bool remove();

    ArrayList<String> list();

    ArrayList<File> listFiles();

    bool mkdir();

    bool mkdirs();

    bool rename(String name);

    bool setReadOnly();

    bool setWriteOnly();

    bool setExecuteOnly();

    bool setWritable();

    bool setReadable();

    bool setExecutable();

    long getTotalSpace();

    long getFreeSpace();

    long getUsableSpace();

    ~_File();
    
    static const String gPathSeparator;

private:

    static int sFileStatusExit;

    String mPath;

    struct stat *mFileInfo;

    int mExist;

    void updateFileInfo();

    bool createDirectory();

    std::ofstream *fileStream;



};

#endif
