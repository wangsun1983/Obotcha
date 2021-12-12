#ifndef __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "Byte.hpp"
#include "Http2Frame.hpp"

namespace obotcha {

//ref:https://www.rfc-editor.org/rfc/inline-errata/rfc7540.html
/*
+-----------------------------------------------+
|                   0x5 (24)                    |
+---------------+---------------+---------------+
|   0x2 (8)     |    0x0 (8)    |
+-+-------------+---------------+-------------------------------+
|R|                  Stream Identifier (31)                     |
+=+=============================================================+
|E|                  Stream Dependency (31)                     |
+-+-------------+-----------------------------------------------+
| Weight (8)    |
+---------------+
 */

DECLARE_CLASS(Http2PriorityFrame) IMPLEMENTS(Http2Frame){
public:
    _Http2PriorityFrame();

    void import(ByteArray);
    ByteArray toByteArray();

    bool isExclusive();
    void setExclusive(bool);

    uint32_t getDependency();
    void setDependency(uint32_t);

    uint8_t getWeight();
    void setWeight(uint8_t);

private:
    /*
      E: A single-bit flag indicating that the stream dependency is
      exclusive (see Section 5.3). 
    */
    bool exclusive;

    /*
      Stream Dependency:  A 31-bit stream identifier for the stream that
      this stream depends on (see Section 5.3).
     */
    uint32_t dependency;

    /*
      Weight:  An unsigned 8-bit integer representing a priority weight for
      the stream (see Section 5.3).  Add one to the value to obtain a
      weight between 1 and 256.
     */
    uint8_t weight;
};

}

#endif
