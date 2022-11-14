#ifndef __OBOTCHA_HTTP_V2_ERROR_CODE_HPP__
#define __OBOTCHA_HTTP_V2_ERROR_CODE_HPP__

#include "Object.hpp"
#include "String.hpp"

namespace obotcha {

/* 
RFC7540:

NO_ERROR (0x0):  The associated condition is not a result of an
      error.  For example, a GOAWAY might include this code to indicate
      graceful shutdown of a connection.

PROTOCOL_ERROR (0x1):  The endpoint detected an unspecific protocol
    error.  This error is for use when a more specific error code is
    not available.

INTERNAL_ERROR (0x2):  The endpoint encountered an unexpected
    internal error.

FLOW_CONTROL_ERROR (0x3):  The endpoint detected that its peer
    violated the flow-control protocol.

SETTINGS_TIMEOUT (0x4):  The endpoint sent a SETTINGS frame but did
    not receive a response in a timely manner.  See Section 6.5.3
    ("Settings Synchronization").

STREAM_CLOSED (0x5):  The endpoint received a frame after a stream
    was half-closed.

FRAME_SIZE_ERROR (0x6):  The endpoint received a frame with an
    invalid size.

REFUSED_STREAM (0x7):  The endpoint refused the stream prior to
    performing any application processing (see Section 8.1.4 for
    details).

CANCEL (0x8):  Used by the endpoint to indicate that the stream is no
    longer needed.

COMPRESSION_ERROR (0x9):  The endpoint is unable to maintain the
    header compression context for the connection.

CONNECT_ERROR (0xa):  The connection established in response to a
    CONNECT request (Section 8.3) was reset or abnormally closed.

ENHANCE_YOUR_CALM (0xb):  The endpoint detected that its peer is
    exhibiting a behavior that might be generating excessive load.

INADEQUATE_SECURITY (0xc):  The underlying transport has properties
    that do not meet minimum security requirements (see Section 9.2).

HTTP_1_1_REQUIRED (0xd):  The endpoint requires that HTTP/1.1 be used
    instead of HTTP/2.

 */

DECLARE_CLASS(Http2ErrorCode) {

public:
    static const int NoError;
    static const int ProtocolError;
    static const int InternalError;
    static const int FlowControlError;
    static const int SettingTimeout;
    static const int StreamClosed;
    static const int FrameSizeError;
    static const int RefusedStream;
    static const int Cancel;
    static const int CompressionError;
    static const int ConnectError;
    static const int EnhanceYourCalm;
    static const int InadequateSecurity;
    static const int HttpV1Required;

    static const String NoErrorString;
    static const String ProtocolErrorString;
    static const String InternalErrorString;
    static const String FlowControlErrorString;
    static const String SettingTimeoutString;
    static const String StreamClosedString;
    static const String FrameSizeErrorString;
    static const String RefusedStreamString;
    static const String CancelString;
    static const String CompressionErrorString;
    static const String ConnectErrorString;
    static const String EnhanceYourCalmString;
    static const String InadequateSecurityString;
    static const String HttpV1RequiredString;

    String toString(int);
};

}

#endif
