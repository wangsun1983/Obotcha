#ifndef __OBOTCHA_HTTP_FILE_HPP__
#define __OBOTCHA_HTTP_FILE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "File.hpp"
#include "String.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(HttpFile){
public:
    _HttpFile(String realname);
    _HttpFile(File file);
    _HttpFile(File file,String realname);

    String getRealName();
    String getName();
    String getAbsolutePath();
    File getFile();

private:
    String mRealName;
    File mFile;
    
};

}
#endif
