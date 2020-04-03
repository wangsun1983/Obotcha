#ifndef __BYTE_HPP__
#define __BYTE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

#define byte unsigned char

DECLARE_SIMPLE_CLASS(Byte)
{
public:
    _Byte(unsigned char v);

    _Byte(Byte &v);

    void update(byte);

    void update(sp<_Byte>);
    
    byte toValue();

    bool equals(byte p);
    
    bool equals(Byte &p);

    bool equals(const _Byte *p);

    ~_Byte();

private:
    byte val;

};

}
#endif