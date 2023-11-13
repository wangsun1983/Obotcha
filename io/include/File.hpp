#ifndef __OBOTCHA_FILE_HPP__
#define __OBOTCHA_FILE_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"
#include "FileDescriptor.hpp"

namespace obotcha {

DECLARE_CLASS(File) {
public:
    explicit _File(const char *path);

    explicit _File(String path);

    _File();

    String getName() const;

    String getSuffix() const;

    String getNameWithNoSuffix() const;

    String getAbsolutePath() const;

    bool canRead() const;

    bool canWrite() const;

    bool canExecute() const;

    bool exists() const;

    bool isDirectory() const;

    bool isFile() const;

    long lastModified() const;

    long lastAccess() const;

    long lastStatusChanged() const;

    long length() const;

    int createNewFile(int flags=O_CREAT, mode_t mode=0666) const;

    bool removeAll();

    ArrayList<String> list() const;

    ArrayList<File> listFiles();

    bool createDir() const;

    bool createDirs() const;

    int rename(String name);

    int setReadOnly() const;

    int setWriteOnly() const;

    int setExecuteOnly() const;

    int setWritable() const;

    int setReadable() const;

    int setExecutable() const;

    int setMode(mode_t) const;

    mode_t getMode() const;

    FileDescriptor open(int flags = st(IO)::FileControlFlags::ReadWrite,
                        int mode = 0666) const;

    static FileDescriptor Open(String path,
                                int flags = st(IO)::FileControlFlags::ReadWrite,
                                int mode = 0666);

    ~_File() override = default;

    static const String kSeparator;
    static const String kSuffix;

    static bool Exists(String);

private:
    int updateFileInfo(struct stat *info) const;
    void deleteDir(File f);
    String mPath;
};

}
#endif
