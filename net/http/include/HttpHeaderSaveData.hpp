#ifndef __OBOTCHA_HTTP_HEADER_SAVE_DATA_HPP__
#define __OBOTCHA_HTTP_HEADER_SAVE_DATA_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ArrayList.hpp"

namespace obotcha {

DECLARE_CLASS(HttpHeaderSaveData) {

public:
    _HttpHeaderSaveData();
    explicit _HttpHeaderSaveData(String);

    void load(String);

    void set(String);

    String get();

    String toString();
    
    static const String ON;
    static const String OFF;
    
private:
    String saveData;
};

}
#endif
