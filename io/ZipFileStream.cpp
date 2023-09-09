extern "C" {
    #include "zip.h"
    #include "zlib.h"
}

#include <fstream>
#include <string.h>
#include <unistd.h>
#include <utime.h>

#include "ZipFileStream.hpp"
#include "Log.hpp"
#include "MethodNotSupportException.hpp"
#include "Inspect.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

const int _ZipFileStream::MaxFileNameSzie = 256;
const int _ZipFileStream::DefaultWriteBuffSize = 1024*32;

_ZipFileStream::_ZipFileStream() {
    mCrc32 = createCrc32();
}

 [[noreturn]] long _ZipFileStream::read(ByteArray buffer) {
    Trigger(MethodNotSupportException, "ZipStream::read(ByteArray)")
}

 [[noreturn]] long _ZipFileStream::read(ByteArray buffer,uint64_t start) {
    Trigger(MethodNotSupportException, "ZipStream::read(ByteArray)")
}

 [[noreturn]] long _ZipFileStream::read(ByteArray, uint64_t start,uint64_t length) {
    Trigger(MethodNotSupportException, "ZipStream::read(ByteArray)")
}

bool _ZipFileStream::open() { 
    return true; 
}

void _ZipFileStream::close() {
    // Do Nothing
}

int _ZipFileStream::compress(String srcPath, String destPath) {
    Inspect(srcPath == nullptr,-EINVAL)

    File srcFile = createFile(srcPath);
    Inspect(!srcFile->exists(),-EINVAL)

    File destFile = createFile(destPath);
    if (destFile->exists()) {
        destFile->removeAll();
    }

    return minizip(srcFile, destFile, nullptr, nullptr);
}

int _ZipFileStream::compressWithPassword(String srcPath, String destPath,
                                         String password) {
    Inspect(srcPath == nullptr || destPath == nullptr || password == nullptr,-EINVAL)

    File srcFile = createFile(srcPath);
    Inspect(!srcFile->exists(),-ENOENT)

    File destFile = createFile(destPath);
    if (destFile->exists()) {
        destFile->removeAll();
    }

    return minizip(srcFile, destFile, nullptr, password);
}

int _ZipFileStream::writeInZipFile(zipFile zFile, File file) const {
    if (file->isDirectory()) {
        return zipWriteInFileInZip(zFile, nullptr, 0);
    }

    std::fstream f(file->getAbsolutePath()->toChars(),
                   std::ios::binary | std::ios::in);

    int readbuffsize = DefaultWriteBuffSize;
    ByteArray byeArrayData = createByteArray(readbuffsize);
    auto buf = (char *)byeArrayData->toValue();

    while(true) {
        f.read(buf, readbuffsize);
        auto readsize = f.gcount();
        if (readsize == 0) {
            break;
        }
        if(zipWriteInFileInZip(zFile, buf, readsize) < 0) {
            LOG(ERROR)<<"writeInZipFile failed";
            f.close();
            return -1;
        }
    }

    f.close();
    return 0;
}

int _ZipFileStream::minizip(File src, File dest, String currentZipFolder,
                            String password) {
    String srcPath = src->getAbsolutePath();
    String srcName = src->getName();
    srcName = combine(currentZipFolder, srcName);
    int opt_compress_level = Z_DEFAULT_COMPRESSION;

    if (src->isFile()) {
        zipFile zFile;
        int status = APPEND_STATUS_ADDINZIP;
        if (!dest->exists()) {
            dest->createNewFile();
            status = APPEND_STATUS_CREATE;
        }
        
        zFile = zipOpen(dest->getAbsolutePath()->toChars(), status);
        Inspect(zFile == nullptr,-1)

        zip_fileinfo zi = {0};
        getFileTime(src, &zi.tmz_date,&zi.dosDate);

        /* calculate the CRC32 of a file,
               because to encrypt a file, we need known the CRC32 of the file before */
        unsigned long crc = 0;
        if(password != nullptr) {
            crc = mCrc32->encodeFile(src)->toUint64()->toValue();
        }

        //int isLarge = isLargeFile(src->getAbsolutePath()->toChars());
        auto isLarge = (src->length() > 0xffffffff)?1:0;
        if (zipOpenNewFileInZip3_64(zFile, srcName->toChars(), &zi, nullptr, 0, nullptr, 0, nullptr /* comment*/,
                                    Z_DEFLATED, opt_compress_level, 0,
                                    /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
                                    -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, 
                                    (password != nullptr)?password->toChars():nullptr, 
                                    crc,
                                    isLarge) != ZIP_OK) {
            LOG(ERROR)<<"zip open failed";
            zipClose(zFile, nullptr);
            return -1;
        }
        
        int ret = writeInZipFile(zFile, src);
        zipClose(zFile, nullptr);
        if (ret != ZIP_OK) {
            LOG(ERROR)<<"zip write failed,ret is "<<ret;
            return -1;
        }
    } else if (src->isDirectory()) {
        String mfolder = combine(currentZipFolder, src->getName());
        
        ArrayList<File> files = src->listFiles();
        ForEveryOne(currentFile,files) {
            minizip(currentFile, dest, mfolder, password);
        }
    }

    return 0;
}

String _ZipFileStream::combine(String parent, String current) const {
    Inspect(parent == nullptr,current)
    return parent->append("/", current);
}

void _ZipFileStream::getFileTime(File file, 
                                 tm_zip *tmzip, 
                                 [[maybe_unused]]uLong *dt) const {
    struct tm filedate;
    time_t tm_t = 0;

    String path = file->getAbsolutePath();
    if (!path->sameAs("-")) {
        struct stat s; /* results of stat() */
        /* not all systems allow stat'ing a file with / appended */
        if (stat(path->toChars(), &s) == 0) {
            tm_t = s.st_mtime;
        }
    }

    localtime_r(&tm_t, &filedate);
    tmzip->tm_sec = filedate.tm_sec;
    tmzip->tm_min = filedate.tm_min;
    tmzip->tm_hour = filedate.tm_hour;
    tmzip->tm_mday = filedate.tm_mday;
    tmzip->tm_mon = filedate.tm_mon;
    tmzip->tm_year = filedate.tm_year;
}

//----------------- deCompress -----------------//
int _ZipFileStream::deCompress(String srcPath) { 
    return deCompress(srcPath, nullptr); 
}

int _ZipFileStream::deCompress(String srcPath, String destPath) {
    return deCompressWithPassword(srcPath, destPath, nullptr);
}

int _ZipFileStream::deCompressWithPassword(String srcPath, String destPath,
                                           String password) {
    const char *_src = srcPath->toChars();
    const char *_dest = (destPath != nullptr)?destPath->toChars():nullptr;

    int opt_do_extract_withoutpath = 0;
    int opt_overwrite = 0;
    int ret_value = 0;

    unzFile uf = unzOpen64(_src);
    ret_value = doExtract(uf,_dest, opt_do_extract_withoutpath,
                           opt_overwrite, 
                           (password == nullptr)?nullptr:password->toChars());
    unzClose(uf);
    return ret_value;
}

int _ZipFileStream::doExtractCurrentfile(unzFile uf, const char *dest,
                                           const int *popt_extract_without_path,
                                           int *popt_overwrite,
                                           const char *password) {
    char filename_inzip[256] = {0};
    char *filename_withoutpath;
    char *p;
    FILE *fout = nullptr;
    void *buf;
    uInt size_buf;
    unz_file_info64 file_info;

    char filename[256] = {0};
    int err = unzGetCurrentFileInfo64(uf, &file_info, filename,
                                      sizeof(filename_inzip), nullptr, 0, nullptr, 0);
    Inspect(err != UNZ_OK,err)

    size_buf = DefaultWriteBuffSize;
    buf = malloc(size_buf);

    if (dest != nullptr) {
        sprintf(filename_inzip, "%s/%s", dest, filename);
    } else {
        sprintf(filename_inzip, "%s", filename);
    }

    p = filename_withoutpath = filename_inzip;
    while ((*p) != '\0') {
        if (((*p) == '/') || ((*p) == '\\')) {
            filename_withoutpath = p + 1;
        }
        p++;
    }

    if ((*filename_withoutpath) == '\0') {
        if ((*popt_extract_without_path) == 0) {
            createDir(filename_inzip);
        }
    } else {
        const char *write_filename;
        if ((*popt_extract_without_path) == 0) {
            write_filename = filename_inzip;
        } else {
            write_filename = filename_withoutpath;
        }

        err = unzOpenCurrentFilePassword(uf, password);
        if (err != UNZ_OK) {
            LOG(ERROR) << "error is" << err
                       << "with zipfile in unzOpenCurrentFilePassword";
        }

        if (((*popt_overwrite) == 0) && (err == UNZ_OK)) {
            File f = createFile(write_filename);
            if(f->exists()) {
                *popt_overwrite = 1;
            }
        }

        if (err == UNZ_OK) {
            fout = fopen64(write_filename, "wb");
            /* some zipfile don't contain directory alone before file */
            if ((fout == nullptr) && ((*popt_extract_without_path) == 0) &&
                (filename_withoutpath != (char *)filename_inzip)) {
                char c = *(filename_withoutpath - 1);
                *(filename_withoutpath - 1) = '\0';
                File file = createFile(write_filename);
                file->createDirs();
                *(filename_withoutpath - 1) = c;
                fout = fopen64(write_filename, "wb");
            }
        }

        if (fout != nullptr) {
            while(true) {
                if ((err = unzReadCurrentFile(uf, buf, size_buf)) <= 0) {
                    if(err < 0) {
                        LOG(ERROR) << "fail to read current file,error is "<<err;
                    }
                    break;
                }

                if (size_t readsize = fwrite(buf, err, 1, fout);readsize != 1) {
                    LOG(ERROR) << "fail to write current file,err is "<<readsize;
                    break;
                }
            }

            fclose(fout);
            if (err == 0) {
                updateFileDate(write_filename, file_info.dosDate,
                                 file_info.tmu_date);
            }
        }

        unzCloseCurrentFile(uf);
    }

    free(buf);
    return err;
}

int _ZipFileStream::doExtract(unzFile uf, const char *dest,
                               int opt_extract_without_path, int opt_overwrite,
                               const char *password) {
    uLong i;
    unz_global_info64 gi;
    int err;

    // make dest dir
    if (dest != nullptr) {
        createDir(dest);
    }

    if ((err = unzGetGlobalInfo64(uf, &gi)) != UNZ_OK) {
        LOG(ERROR) << "error with zipfile in unzGetGlobalInfo,err is "<<err;
        return -1;
    }

    for (i = 0; i < gi.number_entry; i++) {
        if (doExtractCurrentfile(uf, dest, &opt_extract_without_path,
                                   &opt_overwrite, password) != UNZ_OK) {
            break;
        }

        if ((i + 1) < gi.number_entry) {
            if ((err = unzGoToNextFile(uf)) != UNZ_OK) {
                LOG(ERROR) << "error with zipfile in unzGoToNextFile,err is "<<err;
                break;
            }
        }
    }

    return 0;
}

/* mymkdir and change_file_date are not 100 % portable
   As I don't know well Unix, I wait feedback for the unix portion */

int _ZipFileStream::createDir(const char *dirname) const {
    return ::mkdir(dirname, 0775);
}

void _ZipFileStream::updateFileDate(const char *filename, [[maybe_unused]] uLong dosdate,
                                      tm_unz tmu_date) const {
    struct utimbuf ut;
    struct tm newdate;
    newdate.tm_sec = tmu_date.tm_sec;
    newdate.tm_min = tmu_date.tm_min;
    newdate.tm_hour = tmu_date.tm_hour;
    newdate.tm_mday = tmu_date.tm_mday;
    newdate.tm_mon = tmu_date.tm_mon;
    if (tmu_date.tm_year > 1900) {
        newdate.tm_year = tmu_date.tm_year - 1900;
    } else {
        newdate.tm_year = tmu_date.tm_year;
    }
    newdate.tm_isdst = -1;

    ut.actime = ut.modtime = mktime(&newdate);
    utime(filename, &ut);
}

} // namespace obotcha