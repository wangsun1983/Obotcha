#ifndef __OBOTCHA_HTTP_V2_STREAM_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"
#include "Http2Frame.hpp"
#include "Http2Packet.hpp"
#include "OutputStream.hpp"
#include "HttpPacketParser.hpp"
#include "HttpPacketWriter.hpp"

namespace obotcha {

/*
RFC7540
5.1.  Stream States

The lifecycle of a stream is shown in Figure 2.
                        +--------+
                send PP |        | recv PP
                ,--------|  idle  |--------.
                /         |        |         \
                v          +--------+          v
        +----------+          |           +----------+
        |          |          | send H /  |          |
,------| reserved |          | recv H    | reserved |------.
|      | (local)  |          |           | (remote) |      |
|      +----------+          v           +----------+      |
|          |             +--------+             |          |
|          |     recv ES |        | send ES     |          |
|   send H |     ,-------|  open  |-------.     | recv H   |
|          |    /        |        |        \    |          |
|          v   v         +--------+         v   v          |
|      +----------+          |           +----------+      |
|      |   half   |          |           |   half   |      |
|      |  closed  |          | send R /  |  closed  |      |
|      | (remote) |          | recv R    | (local)  |      |
|      +----------+          |           +----------+      |
|           |                |                 |           |
|           | send ES /      |       recv ES / |           |
|           | send R /       v        send R / |           |
|           | recv R     +--------+   recv R   |           |
| send R /  `----------->|        |<-----------'  send R / |
| recv R                 | closed |               recv R   |
`----------------------->|        |<----------------------'
                        +--------+

send:   endpoint sends this frame
recv:   endpoint receives this frame

H:  HEADERS frame (with implied CONTINUATIONs)
PP: PUSH_PROMISE frame (with implied CONTINUATIONs)
ES: END_STREAM flag
R:  RST_STREAM frame


open:
    A stream in the "open" state may be used by both peers to send
    frames of any type.  In this state, sending peers observe
    advertised stream-level flow-control limits (Section 5.2).

    From this state, either endpoint can send a frame with an
    END_STREAM flag set, which causes the stream to transition into
    one of the "half-closed" states.  An endpoint sending an

    END_STREAM flag causes the stream state to become "half-closed
    (local)"; an endpoint receiving an END_STREAM flag causes the
    stream state to become "half-closed (remote)".

    Either endpoint can send a RST_STREAM frame from this state,
    causing it to transition immediately to "closed".
 */
class _Http2Stream;

DECLARE_CLASS(Http2StreamState) {
public:
    _Http2StreamState(_Http2Stream *);
    virtual Http2Packet onReceived(Http2Frame) = 0;
    virtual bool onSend(Http2Frame) = 0;
    int state();

protected:
    int mState;
    _Http2Stream * stream;
};

#define GEN_HTTP2_STATE(X) \
DECLARE_CLASS(Http2Stream##X) IMPLEMENTS(Http2StreamState) {\
public:\
    _Http2Stream##X(_Http2Stream *);\
    Http2Packet onReceived(Http2Frame);\
    bool onSend(Http2Frame);\
};\

GEN_HTTP2_STATE(Idle)
GEN_HTTP2_STATE(ReservedLocal)
GEN_HTTP2_STATE(ReservedRemote)
GEN_HTTP2_STATE(Open)
GEN_HTTP2_STATE(HalfClosedLocal)
GEN_HTTP2_STATE(HalfClosedRemote)
GEN_HTTP2_STATE(Closed)

DECLARE_CLASS(Http2Stream) IMPLEMENTS(HttpPacketWriter){
public:
    friend class _Http2StreamIdle;
    friend class _Http2StreamReservedLocal;
    friend class _Http2StreamReservedRemote;
    friend class _Http2StreamOpen;
    friend class _Http2StreamHalfClosedLocal;
    friend class _Http2StreamHalfClosedRemote;
    friend class _Http2StreamClosed;
    
    enum Status {
        //Http2 status
        Idle = 0,
        ReservedLocal,
        ReservedRemote,
        Open,
        HalfClosedLocal,
        HalfClosedRemote,
        Closed,
    };
    
    _Http2Stream(HPackEncoder,HPackDecoder,int,OutputStream stream = nullptr);
    _Http2Stream(HPackEncoder,HPackDecoder,bool isServer = true,OutputStream stream = nullptr);
    
    int getStreamId();
    void setStreamId(int);

    Http2Packet applyFrame(Http2Frame);
    void sendFrame(Http2Frame);

    //TODO
    int write(HttpPacket);
    ByteArray data(HttpPacket);

    int getStatus();

private:
    Http2StreamIdle IdleState;
    Http2StreamReservedLocal ReservedLocalState;
    Http2StreamReservedRemote ReservedRemoteState;
    Http2StreamOpen OpenState;
    Http2StreamHalfClosedLocal HalfClosedLocalState;
    Http2StreamHalfClosedRemote HalfClosedRemoteState;
    Http2StreamClosed ClosedState;
    Http2StreamState mState;

    static const char* IdleString;
    static const char* ReservedLocalString;
    static const char* ReservedRemoteString;
    static const char* OpenString;
    static const char* HalfClosedLocalString;
    static const char* HalfClosedRemoteString;
    static const char* ClosedString;

    const char *stateToString(int);
    
    void moveTo(Http2StreamState);
    
    int mStreamId;
    bool isServer;

    static std::atomic_int mServerStreamId;
    static std::atomic_int mClientStreamId;
    
    HPackEncoder encoder;
    HPackDecoder decoder;

    HttpHeader header;

    OutputStream out;

};

}

#endif
