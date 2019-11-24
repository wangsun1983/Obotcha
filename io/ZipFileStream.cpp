#include "ZipFileStream.hpp"
#include "Error.hpp"
#include "MethodNotSupportException.hpp"
#include "Log.hpp"

extern "C"
{
#include "zip.h"
#include "zlib.h"
}

#include <fstream>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#include <utime.h>
#endif

#define CASESENSITIVITY (0)
#define MAXFILENAME (256)
#define WRITEBUFFERSIZE 1024 * 32

#ifdef __APPLE__
// In darwin and perhaps other BSD variants off_t is a 64 bit value, hence no need for specific 64 bit functions
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

#define TAG "ZipStream"

namespace obotcha
{

_ZipStream::_ZipStream()
{
}

int _ZipStream::read()
{
    throw createMethodNotSupportException(createString("ZipStream::read()"));
    return 0;
}

long _ZipStream::read(ByteArray buffer)
{
    throw createMethodNotSupportException(createString("ZipStream::read(ByteArray)"));
    return -1;
}

bool _ZipStream::open()
{
    return true;
}

void _ZipStream::close()
{
    //Do Nothing
}

int _ZipStream::compress(String src, String dest)
{
    if (src == nullptr)
    {
        return -InvalidParam;
    }

    File srcFile = createFile(src);
    if (!srcFile->exists())
    {
        return -InvalidParam;
    }

    File destFile = createFile(dest);
    if (destFile->exists())
    {
        destFile->removeAll();
    }

    if (minizip(srcFile, destFile, nullptr, nullptr) == -1)
    {
        return -MiniZipFail;
    }

    return 0;
}

ByteArray _ZipStream::compress(ByteArray value) {
    //TODO
}


int _ZipStream::compressWithPassword(String src, String dest, String password)
{
    if (src == nullptr || dest == nullptr || password == nullptr)
    {
        return -InvalidParam;
    }

    File srcFile = createFile(src);
    if (!srcFile->exists())
    {
        return -InvalidParam;
    }

    File destFile = createFile(dest);
    if (destFile->exists())
    {
        destFile->removeAll();
    }

    if (minizip(srcFile, destFile, nullptr, (char *)password->toChars()) == -1)
    {
        return -MiniZipFail;
    }

    return 0;
}

int _ZipStream::writeInZipFile(zipFile zFile, File file)
{
    if (file->isDirectory())
    {
        return zipWriteInFileInZip(zFile, NULL, 0);
    }

    std::fstream f(file->getAbsolutePath()->toChars(), std::ios::binary | std::ios::in);
    f.seekg(0, std::ios::end);
    long filesize = f.tellg();
    f.seekg(0, std::ios::beg);

    int readbuffsize = WRITEBUFFERSIZE;
    char *buf = new char[readbuffsize];
    int ret = 0;
    while (1)
    {
        f.read(buf, readbuffsize);
        int readsize = f.gcount();
        if (readsize == 0)
        {
            break;
        }

        ret = zipWriteInFileInZip(zFile, buf, readsize);
    }

    delete[] buf;
    f.close();
    return ret;
}

int _ZipStream::minizip(File src, File dest, String currentZipFolder, char *password)
{
    String srcPath = src->getAbsolutePath();
    String destPath = dest->getAbsolutePath();
    String srcName = src->getName();
    srcName = combine(currentZipFolder, srcName);
    int opt_compress_level = Z_DEFAULT_COMPRESSION;

    if (src->isFile())
    {
        zipFile zFile;
        if (!dest->exists())
        {
            zFile = zipOpen(destPath->toChars(), APPEND_STATUS_CREATE);
        }
        else
        {
            zFile = zipOpen(destPath->toChars(), APPEND_STATUS_ADDINZIP);
        }

        if (zFile == NULL)
        {
            return -1;
        }

        zip_fileinfo zi = {0};
        zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
            zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
        zi.dosDate = 0;
        zi.internal_fa = 0;
        zi.external_fa = 0;
        filetime((const char *)src->getAbsolutePath()->toChars(), &zi.tmz_date, &zi.dosDate);

        char *buf = nullptr;
        unsigned long crcFile = 0;

        if (password != nullptr)
        {
            buf = (char *)malloc(WRITEBUFFERSIZE);
            getFileCrc(src->getAbsolutePath()->toChars(), buf, WRITEBUFFERSIZE, &crcFile);
        }

        if (buf != nullptr)
        {
            free(buf);
        }

        int isLarge = isLargeFile(src->getAbsolutePath()->toChars());

        //int ret = zipOpenNewFileInZip(zFile, srcName->toChars(), &zi, NULL, 0, NULL, 0, NULL, 0, 0);
        int ret = zipOpenNewFileInZip3_64(zFile, srcName->toChars(), &zi,
                                          NULL, 0, NULL, 0, NULL /* comment*/,
                                          (opt_compress_level != 0) ? Z_DEFLATED : 0,
                                          opt_compress_level, 0,
                                          /* -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY, */
                                          -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                          password, crcFile, isLarge);

        if (ret != ZIP_OK)
        {
            zipClose(zFile, NULL);
            return -1;
        }

        ret = writeInZipFile(zFile, src);
        if (ret != ZIP_OK)
        {
            zipClose(zFile, NULL);
            return -1;
        }
        zipClose(zFile, NULL);
    }
    else if (src->isDirectory())
    {
        zip_fileinfo zFileInfo = {0};

        String mfolder = combine(currentZipFolder, src->getName());

        vector<string> vFiles;
        ArrayList<File> files = src->listFiles();
        ListIterator<File> iterator = files->getIterator();

        while (iterator->hasValue())
        {
            File currentSrcFile = iterator->getValue();
            minizip(currentSrcFile, dest, mfolder, password);
            iterator->next();
        }

        cout << "zip ok" << endl;
    }
    return 0;
}

String _ZipStream::combine(String parent, String current)
{
    if (parent == nullptr)
    {
        return current;
    }

    String mfolder = createString(parent);
    mfolder->append("/");
    mfolder->append(current);

    return mfolder;
}

uLong _ZipStream::filetime(const char *file, tm_zip *tmzip, uLong *dt)
{
    int ret = 0;
    struct stat s; /* results of stat() */
    struct tm filedate;
    time_t tm_t = 0;

    if (strcmp(file, "-") != 0)
    {
        char name[MAXFILENAME + 1];
        int len = strlen(file);
        if (len > MAXFILENAME)
            len = MAXFILENAME;

        strncpy(name, file, MAXFILENAME - 1);
        /* strncpy doesnt append the trailing NULL, of the string is too long. */
        name[MAXFILENAME] = '\0';

        if (name[len - 1] == '/')
            name[len - 1] = '\0';
        /* not all systems allow stat'ing a file with / appended */
        if (stat(name, &s) == 0)
        {
            tm_t = s.st_mtime;
            ret = 1;
        }
    }

    localtime_r(&tm_t, &filedate);

    tmzip->tm_sec = filedate.tm_sec;
    tmzip->tm_min = filedate.tm_min;
    tmzip->tm_hour = filedate.tm_hour;
    tmzip->tm_mday = filedate.tm_mday;
    tmzip->tm_mon = filedate.tm_mon;
    tmzip->tm_year = filedate.tm_year;
    return ret;
}

/* calculate the CRC32 of a file,
   because to encrypt a file, we need known the CRC32 of the file before */
int _ZipStream::getFileCrc(const char *filenameinzip, char *buf, unsigned long size_buf, unsigned long *result_crc)
{
    unsigned long calculate_crc = 0;
    int err = ZIP_OK;
    FILE *fin = FOPEN_FUNC(filenameinzip, "rb");

    unsigned long size_read = 0;
    unsigned long total_read = 0;
    if (fin == NULL)
    {
        err = ZIP_ERRNO;
    }

    if (err == ZIP_OK)
    {
        do
        {
            err = ZIP_OK;
            size_read = (int)fread(buf, 1, size_buf, fin);
            if (size_read < size_buf)
            {
                if (feof(fin) == 0)
                {
                    err = ZIP_ERRNO;
                }
            }

            if (size_read > 0)
            {
                calculate_crc = crc32(calculate_crc, (Bytef *)buf, size_read);
            }
            total_read += size_read;

        } while ((err == ZIP_OK) && (size_read > 0));
    }

    if (fin)
    {
        fclose(fin);
    }

    *result_crc = calculate_crc;
    return err;
}

int _ZipStream::isLargeFile(const char *filename)
{
    int largeFile = 0;
    ZPOS64_T pos = 0;
    FILE *pFile = FOPEN_FUNC(filename, "rb");

    if (pFile != NULL)
    {

        FSEEKO_FUNC(pFile, 0, SEEK_END);

        pos = FTELLO_FUNC(pFile);

        if (pos >= 0xffffffff)
        {
            largeFile = 1;
        }

        fclose(pFile);
    }
    return largeFile;
}

//----------------- uncompress -----------------//
//int _ZipStream::uncompress(const char *src) {
//    return uncompress(src,nullptr);
//}

//int _ZipStream::uncompress(const char *src,const char *dest) {
//    return uncompressWithPassword(src,dest,(const char *)nullptr);
//}

//int _ZipStream::uncompressWithPassword(const char *src,const char *dest,const char *password) {
//    int opt_do_extract_withoutpath = 0;
//    int opt_overwrite = 0;
//    int ret_value = 0;

//    unzFile uf = unzOpen64(src);
//    if(password == nullptr) {
//        ret_value = do_extract(uf, (char *)dest,opt_do_extract_withoutpath, opt_overwrite, nullptr);
//    } else {
//        ret_value = do_extract(uf, (char *)dest,opt_do_extract_withoutpath, opt_overwrite, password);
//    }

//    return ret_value;
//}

int _ZipStream::uncompress(String src)
{
    return uncompress(src, nullptr);
}

int _ZipStream::uncompress(String src, String dest)
{
    return uncompressWithPassword(src, dest, nullptr);
}

int _ZipStream::uncompressWithPassword(String src, String dest, String password)
{
    char *_src = (char *)src->toChars();
    char *_dest = nullptr;
    char *_password = nullptr;

    if (dest != nullptr)
    {
        _dest = (char *)dest->toChars();
    }

    if (password != nullptr)
    {
        _password = (char *)password->toChars();
    }

    int opt_do_extract_withoutpath = 0;
    int opt_overwrite = 0;
    int ret_value = 0;

    unzFile uf = unzOpen64(_src);
    if (password == nullptr)
    {
        ret_value = do_extract(uf, (char *)_dest, opt_do_extract_withoutpath, opt_overwrite, nullptr);
    }
    else
    {
        ret_value = do_extract(uf, (char *)_dest, opt_do_extract_withoutpath, opt_overwrite, _password);
    }

    return ret_value;
}

int _ZipStream::do_extract_currentfile(unzFile uf, char *dest, const int *popt_extract_without_path,
                                       int *popt_overwrite,
                                       const char *password)
{
    char filename_inzip[256];
    char *filename_withoutpath;
    char *p;
    FILE *fout = NULL;
    void *buf;
    uInt size_buf;

    unz_file_info64 file_info;
#if 0    
    uLong ratio=0;
#endif
    char _filename[256];
    int err = unzGetCurrentFileInfo64(uf, &file_info, _filename, sizeof(filename_inzip), NULL, 0, NULL, 0);

    if (err != UNZ_OK)
    {
        return err;
    }

    size_buf = WRITEBUFFERSIZE;
    buf = (void *)malloc(size_buf);
    if (buf == NULL)
    {
        return UNZ_INTERNALERROR;
    }

    if (dest != nullptr)
    {
        sprintf(filename_inzip, "%s/%s", dest, _filename);
    }
    else
    {
        sprintf(filename_inzip, "%s", _filename);
    }

    p = filename_withoutpath = filename_inzip;
    while ((*p) != '\0')
    {
        if (((*p) == '/') || ((*p) == '\\'))
            filename_withoutpath = p + 1;
        p++;
    }

    if ((*filename_withoutpath) == '\0')
    {
        if ((*popt_extract_without_path) == 0)
        {
            mymkdir(filename_inzip);
        }
    }
    else
    {
        const char *write_filename;

        if ((*popt_extract_without_path) == 0)
        {
            write_filename = filename_inzip;
        }
        else
        {
            write_filename = filename_withoutpath;
        }

        err = unzOpenCurrentFilePassword(uf, password);
        if (err != UNZ_OK)
        {
            LOGE(TAG, "error is ", err, "with zipfile in unzOpenCurrentFilePassword");
        }

        if (((*popt_overwrite) == 0) && (err == UNZ_OK))
        {
            char rep = 0;
            FILE *ftestexist;
            ftestexist = FOPEN_FUNC(write_filename, "rb");
            if (ftestexist != NULL)
            {
                fclose(ftestexist);
            }

            *popt_overwrite = 1;
        }

        if(err == UNZ_OK)
        {
            fout = FOPEN_FUNC(write_filename, "wb");
            /* some zipfile don't contain directory alone before file */
            if ((fout == NULL) && ((*popt_extract_without_path) == 0) &&
                (filename_withoutpath != (char *)filename_inzip))
            {
                char c = *(filename_withoutpath - 1);
                *(filename_withoutpath - 1) = '\0';
                makedir((char *)write_filename);
                *(filename_withoutpath - 1) = c;
                fout = FOPEN_FUNC(write_filename, "wb");
            }

            if (fout == NULL)
            {
                LOGE(TAG,"error opening ",write_filename);
            }
        }

        if (fout != NULL)
        {
            do
            {
                err = unzReadCurrentFile(uf, buf, size_buf);
                if (err < 0)
                {
                    LOGE(TAG,"error ",err,"with zipfile in unzReadCurrentFile");
                    break;
                }
                if (err > 0)
                    if (fwrite(buf, err, 1, fout) != 1)
                    {
                        LOGE(TAG,"error in writing extracted file");
                        err = UNZ_ERRNO;
                        break;
                    }
            } while (err > 0);
            if (fout)
                fclose(fout);

            if (err == 0)
                change_file_date(write_filename, file_info.dosDate,
                                 file_info.tmu_date);
        }

        if (err == UNZ_OK)
        {
            err = unzCloseCurrentFile(uf);
            if (err != UNZ_OK)
            {
                LOGE(TAG,"error ",err," with zipfile in unzCloseCurrentFile\n");
            }
        }
        else
            unzCloseCurrentFile(uf); /* don't lose the error */
    }

    free(buf);
    return err;
}

int _ZipStream::do_extract(unzFile uf, char *dest, int opt_extract_without_path, int opt_overwrite, const char *password)
{
    uLong i;
    unz_global_info64 gi;
    int err;
#if 0    
    FILE* fout=NULL;
#endif
    //make dest dir
    if (dest != nullptr)
    {
        mymkdir(dest);
    }

    err = unzGetGlobalInfo64(uf, &gi);
    if (err != UNZ_OK) {
        LOGE(TAG,"error ",err,"with zipfile in unzGetGlobalInfo \n");
    }

    for (i = 0; i < gi.number_entry; i++)
    {
        if (do_extract_currentfile(uf, dest, &opt_extract_without_path,
                                   &opt_overwrite,
                                   password) != UNZ_OK)
            break;

        if ((i + 1) < gi.number_entry)
        {
            err = unzGoToNextFile(uf);
            if (err != UNZ_OK)
            {
                LOGE(TAG,"error ",err," with zipfile in unzGoToNextFile\n");
                break;
            }
        }
    }

    return 0;
}

/* mymkdir and change_file_date are not 100 % portable
   As I don't know well Unix, I wait feedback for the unix portion */

int _ZipStream::mymkdir(const char *dirname)
{
    int ret = 0;
#ifdef _WIN32
    ret = _mkdir(dirname);
#elif unix
    ret = mkdir(dirname, 0775);
#elif __APPLE__
    ret = mkdir(dirname, 0775);
#endif
    return ret;
}

int _ZipStream::makedir(char *newdir)
{
    char *buffer;
    char *p;
    int len = (int)strlen(newdir);

    if (len <= 0)
        return 0;

    buffer = (char *)malloc(len + 1);
    if (buffer == NULL)
    {
        return UNZ_INTERNALERROR;
    }
    strcpy(buffer, newdir);

    if (buffer[len - 1] == '/')
    {
        buffer[len - 1] = '\0';
    }
    if (mymkdir(buffer) == 0)
    {
        free(buffer);
        return 1;
    }

    p = buffer + 1;
    while (1)
    {
        char hold;

        while (*p && *p != '\\' && *p != '/')
            p++;
        hold = *p;
        *p = 0;
        if ((mymkdir(buffer) == -1) && (errno == ENOENT))
        {
            LOGE(TAG,"couldn't create directory \n");
            free(buffer);
            return 0;
        }
        if (hold == 0)
            break;
        *p++ = hold;
    }
    free(buffer);
    return 1;
}

void _ZipStream::change_file_date(
    const char *filename,
    uLong dosdate,
    tm_unz tmu_date)
{
#ifdef _WIN32
    HANDLE hFile;
    FILETIME ftm, ftLocal, ftCreate, ftLastAcc, ftLastWrite;

    hFile = CreateFileA(filename, GENERIC_READ | GENERIC_WRITE,
                        0, NULL, OPEN_EXISTING, 0, NULL);
    GetFileTime(hFile, &ftCreate, &ftLastAcc, &ftLastWrite);
    DosDateTimeToFileTime((WORD)(dosdate >> 16), (WORD)dosdate, &ftLocal);
    LocalFileTimeToFileTime(&ftLocal, &ftm);
    SetFileTime(hFile, &ftm, &ftLastAcc, &ftm);
    CloseHandle(hFile);
#else
#if (defined unix) || (defined __APPLE__)
    struct utimbuf ut;
    struct tm newdate;
    newdate.tm_sec = tmu_date.tm_sec;
    newdate.tm_min = tmu_date.tm_min;
    newdate.tm_hour = tmu_date.tm_hour;
    newdate.tm_mday = tmu_date.tm_mday;
    newdate.tm_mon = tmu_date.tm_mon;
    if (tmu_date.tm_year > 1900)
        newdate.tm_year = tmu_date.tm_year - 1900;
    else
        newdate.tm_year = tmu_date.tm_year;
    newdate.tm_isdst = -1;

    ut.actime = ut.modtime = mktime(&newdate);
    utime(filename, &ut);
#endif
#endif
}

} // namespace obotcha