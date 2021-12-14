#ifndef __OBOTCHA_HTTP_V2_STREAM_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_HPP__

#include <atomic>

#include "Object.hpp"
#include "StrongPointer.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"

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

DECLARE_CLASS(Http2Stream) {
public:
    enum Status {
        Idle = 0,
        ReservedLocal,
        ReservedRemote,
        Open,
        HalfClosedLocal,
        HalfClosedRemote,
        Closed,
    };
    
    _Http2Stream(HPackEncoder,HPackDecoder,int);
    _Http2Stream(HPackEncoder,HPackDecoder,bool isServer = true);
    
    int getStreamId();
    void setStreamId(int);

    int getStatus();

private:
    int mStreamId;
    bool isServer;

    int mStatus;

    static std::atomic_int mServerStreamId;
    static std::atomic_int mClientStreamId;
    
    HPackEncoder encoder;
    HPackDecoder decoder;
};

}

#endif
