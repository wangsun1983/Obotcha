#ifndef __OBOTCHA_HTTP_MULIT_PART_HPP__
#define __OBOTCHA_HTTP_MULIT_PART_HPP__

#include "Object.hpp"
#include "ArrayList.hpp"
#include "File.hpp"
#include "Pair.hpp"
#include "String.hpp"
#include "HttpHeaderContentType.hpp"

namespace obotcha {

DECLARE_CLASS(HttpMultiPartFile) {

public:
    _HttpMultiPartFile(String filename,String name = nullptr,HttpHeaderContentType contentType = nullptr);
    _HttpMultiPartFile(File file,String name = nullptr,HttpHeaderContentType contentType = nullptr);

    String getName();
    String getOriginalFileName();
    HttpHeaderContentType getContentType();
    File getFile();

private:
    void updateContentType(String suffix);
    File mFile;
    String mName;
    String mOriginalFileName;
    HttpHeaderContentType mContentType;
};

DECLARE_CLASS(HttpMultiPart) {
public:
    friend class _HttpPacketWriterImpl;
    _HttpMultiPart();
    explicit _HttpMultiPart(String boundary);
    void addFile(File,String name = nullptr);
    void addFile(HttpMultiPartFile);

    void addContent(String name,String value);
    ArrayList<HttpMultiPartFile> getFiles();
    ArrayList<Pair<String, String>> getContents();
        
    String getBoundary();
    long getContentLength();
private:
    ArrayList<HttpMultiPartFile> files = createArrayList<HttpMultiPartFile>();
    ArrayList<Pair<String, String>> contents = createArrayList<Pair<String, String>>();

    String mBoundary;

    using composeCallBack = std::function<void(ByteArray)>;
    void onCompose(composeCallBack callback);
};

} // namespace obotcha
#endif
