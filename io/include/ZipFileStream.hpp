#ifndef __OBOTCHA_ZIP_INPUT_STREAM_HPP__
#define __OBOTCHA_ZIP_INPUT_STREAM_HPP__

extern "C" {
    #include "unzip.h"
    #include "zip.h"
    #include "zlib.h"
}

#include <fstream>

#include "Object.hpp"
#include "ByteArray.hpp"
#include "File.hpp"
#include "InputStream.hpp"
#include "String.hpp"
#include "ZipFile.hpp"
#include "Crc32.hpp"

namespace obotcha {

DECLARE_CLASS(ZipFileStream) IMPLEMENTS(InputStream) {
public:
    _ZipFileStream();

     [[noreturn]] long read(ByteArray buffer) final;

     [[noreturn]] long read(ByteArray, int start) final;

     [[noreturn]] long read(ByteArray, int start,int length) final;

    bool open() final;

    void close() final;

    int compress(String srcPath, String destPath);

    int compressWithPassword(String srcPath, String destPath, String password);

    int deCompress(String srcPath);

    int deCompress(String srcPath, String destPath);

    int deCompressWithPassword(String srcPath, String destPath, String password);

private:
    static const int MaxFileNameSzie;
    static const int DefaultWriteBuffSize;

    String mPath;

    Crc32 mCrc32;

    std::ifstream fstream;

    int writeInZipFile(zipFile zFile, File file);

    int minizip(File src, File dest, String zipfolder, String password);

    String combine(String parent, String current);

    void getFileTime(File file, tm_zip *tmzip, uLong *dt);

    // uncompress interface
    int doExtractCurrentfile(unzFile uf, const char *dest,
                               const int *popt_extract_without_path,
                               int *popt_overwrite, const char *password);

    int doExtract(unzFile uf, const char *dest, int opt_extract_without_path,
                   int opt_overwrite, const char *password);

    int createDir(const char *dirname);

    void updateFileDate(const char *filename, uLong dosdate, tm_unz tmu_date);
};

} // namespace obotcha
#endif
