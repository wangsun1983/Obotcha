#ifndef __OBOTCHA_HTTP_V2_STREAM_HPP__
#define __OBOTCHA_HTTP_V2_STREAM_HPP__

#include <atomic>

#include "Object.hpp"
#include "HPackEncoder.hpp"
#include "HPackDecoder.hpp"
#include "Http2Frame.hpp"
#include "Http2Packet.hpp"
#include "Http2StreamSender.hpp"
#include "Http2RemoteFlowController.hpp"
#include "Http2LocalFlowController.hpp"
#include "Http2FrameTransmitter.hpp"
#include "Http2FrameByteArray.hpp"

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


Streams have the following states:

idle:
    All streams start in the "idle" state.

    The following transitions are valid from this state:

    *  Sending or receiving a HEADERS frame causes the stream to
        become "open".  The stream identifier is selected as described
        in Section 5.1.1.  The same HEADERS frame can also cause a
        stream to immediately become "half-closed".

    *  Sending a PUSH_PROMISE frame on another stream reserves the
        idle stream that is identified for later use.  The stream state
        for the reserved stream transitions to "reserved (local)".

    *  Receiving a PUSH_PROMISE frame on another stream reserves an
        idle stream that is identified for later use.  The stream state
        for the reserved stream transitions to "reserved (remote)".

    *  Note that the PUSH_PROMISE frame is not sent on the idle stream
        but references the newly reserved stream in the Promised Stream
        ID field.

    Receiving any frame other than HEADERS or PRIORITY on a stream in
    this state MUST be treated as a connection error (Section 5.4.1)
    of type PROTOCOL_ERROR.

reserved (local):
    A stream in the "reserved (local)" state is one that has been
    promised by sending a PUSH_PROMISE frame.  A PUSH_PROMISE frame
    reserves an idle stream by associating the stream with an open
    stream that was initiated by the remote peer (see Section 8.2).

    In this state, only the following transitions are possible:

    *  The endpoint can send a HEADERS frame.  This causes the stream
        to open in a "half-closed (remote)" state.

    *  Either endpoint can send a RST_STREAM frame to cause the stream
        to become "closed".  This releases the stream reservation.


    An endpoint MUST NOT send any type of frame other than HEADERS,
    RST_STREAM, or PRIORITY in this state.

    A PRIORITY or WINDOW_UPDATE frame MAY be received in this state.
    Receiving any type of frame other than RST_STREAM, PRIORITY, or
    WINDOW_UPDATE on a stream in this state MUST be treated as a
    connection error (Section 5.4.1) of type PROTOCOL_ERROR.

reserved (remote):
    A stream in the "reserved (remote)" state has been reserved by a
    remote peer.

    In this state, only the following transitions are possible:

    *  Receiving a HEADERS frame causes the stream to transition to
        "half-closed (local)".

    *  Either endpoint can send a RST_STREAM frame to cause the stream
        to become "closed".  This releases the stream reservation.

    An endpoint MAY send a PRIORITY frame in this state to
    reprioritize the reserved stream.  An endpoint MUST NOT send any
    type of frame other than RST_STREAM, WINDOW_UPDATE, or PRIORITY in
    this state.

    Receiving any type of frame other than HEADERS, RST_STREAM, or
    PRIORITY on a stream in this state MUST be treated as a connection
    error (Section 5.4.1) of type PROTOCOL_ERROR.

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

half-closed (local):
    A stream that is in the "half-closed (local)" state cannot be used
    for sending frames other than WINDOW_UPDATE, PRIORITY, and
    RST_STREAM.

    A stream transitions from this state to "closed" when a frame that
    contains an END_STREAM flag is received or when either peer sends
    a RST_STREAM frame.

    An endpoint can receive any type of frame in this state.
    Providing flow-control credit using WINDOW_UPDATE frames is
    necessary to continue receiving flow-controlled frames.  In this
    state, a receiver can ignore WINDOW_UPDATE frames, which might
    arrive for a short period after a frame bearing the END_STREAM
    flag is sent.

    PRIORITY frames received in this state are used to reprioritize
    streams that depend on the identified stream.

half-closed (remote):
    A stream that is "half-closed (remote)" is no longer being used by
    the peer to send frames.  In this state, an endpoint is no longer
    obligated to maintain a receiver flow-control window.

    If an endpoint receives additional frames, other than
    WINDOW_UPDATE, PRIORITY, or RST_STREAM, for a stream that is in
    this state, it MUST respond with a stream error (Section 5.4.2) of
    type STREAM_CLOSED.

    A stream that is "half-closed (remote)" can be used by the
    endpoint to send frames of any type.  In this state, the endpoint
    continues to observe advertised stream-level flow-control limits
    (Section 5.2).

    A stream can transition from this state to "closed" by sending a
    frame that contains an END_STREAM flag or when either peer sends a
    RST_STREAM frame.

closed:
    The "closed" state is the terminal state.

    An endpoint MUST NOT send frames other than PRIORITY on a closed
    stream.  An endpoint that receives any frame other than PRIORITY
    after receiving a RST_STREAM MUST treat that as a stream error
    (Section 5.4.2) of type STREAM_CLOSED.  Similarly, an endpoint
    that receives any frames after receiving a frame with the
    END_STREAM flag set MUST treat that as a connection error
    (Section 5.4.1) of type STREAM_CLOSED, unless the frame is
    permitted as described below.

    WINDOW_UPDATE or RST_STREAM frames can be received in this state
    for a short period after a DATA or HEADERS frame containing an
    END_STREAM flag is sent.  Until the remote peer receives and
    processes RST_STREAM or the frame bearing the END_STREAM flag, it
    might send frames of these types.  Endpoints MUST ignore
    WINDOW_UPDATE or RST_STREAM frames received in this state, though
    endpoints MAY choose to treat frames that arrive a significant
    time after sending END_STREAM as a connection error
    (Section 5.4.1) of type PROTOCOL_ERROR.

    PRIORITY frames can be sent on closed streams to prioritize
    streams that are dependent on the closed stream.  Endpoints SHOULD
    process PRIORITY frames, though they can be ignored if the stream
    has been removed from the dependency tree (see Section 5.3.4).

    If this state is reached as a result of sending a RST_STREAM
    frame, the peer that receives the RST_STREAM might have already
    sent -- or enqueued for sending -- frames on the stream that
    cannot be withdrawn.  An endpoint MUST ignore frames that it
    receives on closed streams after it has sent a RST_STREAM frame.
    An endpoint MAY choose to limit the period over which it ignores
    frames and treat frames that arrive after this time as being in
    error.

    Flow-controlled frames (i.e., DATA) received after sending
    RST_STREAM are counted toward the connection flow-control window.
    Even though these frames might be ignored, because they are sent
    before the sender receives the RST_STREAM, the sender will
    consider the frames to count against the flow-control window.

    An endpoint might receive a PUSH_PROMISE frame after it sends
    RST_STREAM.  PUSH_PROMISE causes a stream to become "reserved"
    even if the associated stream has been reset.  Therefore, a
    RST_STREAM is needed to close an unwanted promised stream.
 */
class _Http2Stream;

DECLARE_CLASS(Http2StreamState) {
public:
    explicit _Http2StreamState(_Http2Stream *);
    virtual Http2Packet onReceived(Http2Frame) = 0;
    virtual int onSend(Http2Frame) = 0;
    int state() const;

protected:
    int mState = -1;
    _Http2Stream * stream;
};

#define GEN_HTTP2_STATE(X) \
DECLARE_CLASS(Http2Stream##X) IMPLEMENTS(Http2StreamState) {\
public:\
    _Http2Stream##X(_Http2Stream *);\
    Http2Packet onReceived(Http2Frame);\
    int onSend(Http2Frame);\
};\

GEN_HTTP2_STATE(Idle)
GEN_HTTP2_STATE(ReservedLocal)
GEN_HTTP2_STATE(ReservedRemote)
GEN_HTTP2_STATE(Open)
GEN_HTTP2_STATE(HalfClosedLocal)
GEN_HTTP2_STATE(HalfClosedRemote)
GEN_HTTP2_STATE(Closed)

DECLARE_CLASS(Http2Stream) {
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
    
    _Http2Stream(HPackEncoder,HPackDecoder,Http2FrameTransmitter dispatcher,uint32_t id,Http2StreamSender sender = nullptr);
    _Http2Stream(HPackEncoder,HPackDecoder,Http2FrameTransmitter dispatcher,bool isServer = true,Http2StreamSender sender = nullptr);
    
    void setFlowController(Http2RemoteFlowController,Http2LocalFlowController);
    
    int getStreamId() const;
    void setStreamId(int);

    HttpHeader getHeader();

    //wangsl
    Http2Packet applyFrame(Http2Frame);
    //wangsl

    void sendFrame(Http2Frame);

    int write(HttpPacket);

    int getStatus();

    int getPriority();

    void setPriority(int);

    int directWrite(Http2Frame);
    int directWriteData(Http2FrameByteArray framedata);

    Http2StreamState getStreamState();

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

    ByteArray mCacheData;

    void init();
    
    uint32_t mStreamId;
    bool isServer;

    static std::atomic_int mServerStreamId;
    static std::atomic_int mClientStreamId;
    
    HPackEncoder encoder;
    HPackDecoder decoder;

    HttpHeader header;

    Http2StreamSender out;

    int mPriority;

    Http2RemoteFlowController mRemoteController;
    Http2LocalFlowController mLocalController;
    Http2FrameTransmitter mDataDispatcher;
    ByteArray mHeadBlockFragment;
};

}

#endif
