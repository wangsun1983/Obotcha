#ifndef __OBOTCHA_HTTP_CONTENT_DISPOSITION_HPP__
#define __OBOTCHA_HTTP_CONTENT_DISPOSITION_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "ArrayList.hpp"

//https://m.php.cn/manual/view/35599.html

namespace obotcha {

DECLARE_CLASS(HttpHeaderContentDisposition) {

public:
    enum Type {
        Inline = 0,
        Attachment,
        FormData,
    };

    _HttpHeaderContentDisposition();
    _HttpHeaderContentDisposition(String);

    void import(String);
    String toString();

    int getType();
    void setType(int);

    void setFileName(String);
    String getFileName();

    void setName(String);
    String getName();

private:    
    int type;
    String filename;
    String name;
};

}
#endif
