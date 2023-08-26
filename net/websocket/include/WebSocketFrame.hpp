#ifndef __OBOTCHA_WEB_SOCKET_FRAME_HPP__
#define __OBOTCHA_WEB_SOCKET_FRAME_HPP__

#include "Object.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHeader) {
public:
    _WebSocketHeader();

    void clear();
    
    void setOpCode(int);
    int getOpCode() const;

    void setIsFinalFrame(bool);
    bool isFinalFrame() const;

    void setIsControlFrame(bool);
    bool getIsControlFrame() const;

    void setReservedFlag1(bool);
    bool getReservedFlag1() const;

    void setReservedFlag2(bool);
    bool getReservedFlag2() const;

    void setReservedFlag3(bool);
    bool getReservedFlag3() const;

    void setMasked(bool);
    bool getMasked() const;

    void setFrameLength(long);
    long getFrameLength() const;

    void setMaskKey(ByteArray);
    ByteArray getMaskKey() const;

    int getHeadSize() const;
    void setHeadSize(int);

    void setB0(int b0);
    void setB1(int b1);

    int getB0() const;
    int getB1() const;
    
private:
    int mOpcode;
    bool mIsFinalFrame;
    bool mIsControlFrame;
    bool mReservedFlag1;
    bool mReservedFlag2;
    bool mReservedFlag3;
    bool mIsMasked;
    long mFrameLength;
    ByteArray mMaskKey;
    int mHeadSize;

    int mB0;
    int mB1;
};

DECLARE_CLASS(WebSocketFrame) {
public:
    _WebSocketFrame(WebSocketHeader,ByteArray);
    _WebSocketFrame() = default;
    
    void setHeader(WebSocketHeader);
    void setData(ByteArray data);

    WebSocketHeader getHeader();
    ByteArray getData();

    int getCloseStatus() const;
    void setCloseStatus(int);

private:
    WebSocketHeader mHeader = nullptr;
    ByteArray mData = nullptr; 
    int mCloseStatus = -1;
};

}
#endif
