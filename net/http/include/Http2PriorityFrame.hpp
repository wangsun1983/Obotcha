#ifndef __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__
#define __OBOTCHA_HTTP_V2_PRIORITY_FRAME_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"
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

The payload of a PRIORITY frame contains the following fields:

E: A single-bit flag indicating that the stream dependency is
  exclusive (see Section 5.3).

Stream Dependency:  A 31-bit stream identifier for the stream that
  this stream depends on (see Section 5.3).
  the stream on which this stream should depend, or 0 if it should 
  depend on the connection.

Weight:  An unsigned 8-bit integer representing a priority weight for
  the stream (see Section 5.3).  Add one to the value to obtain a
  weight between 1 and 256.

+---------------+
 */

DECLARE_CLASS(Http2PriorityFrame) IMPLEMENTS(Http2Frame){
public:
    _Http2PriorityFrame();

    uint32_t getDependency() const;
    void setDependency(uint32_t);

    void load(ByteArray);
    ByteArray toByteArray();

private:
    uint32_t dependencyStream;
};

}

#endif
