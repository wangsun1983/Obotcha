#ifndef __BYTE_HPP__
#define __BYTE_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

namespace obotcha {

#define byte char

DECLARE_SIMPLE_CLASS(Byte)
{
public:
    _Byte(char v);

    _Byte(Byte v);
    
    char toValue();

    bool equals(char p);
    
    bool equals(Byte p);

    bool equals(_Byte *p);

    ~_Byte();

private:
    char val;

};

}
#endif