#ifndef __OBOTCHA_WEB_SOCKET_FRAME_HPP__
#define __OBOTCHA_WEB_SOCKET_FRAME_HPP__

#include "Object.hpp"
#include "String.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_CLASS(WebSocketHeader) {
public:
    _WebSocketHeader();

    void clear();
    
    void setOpCode(int);
    int getOpCode();

    void setIsFinalFrame(bool);
    bool isFinalFrame();

    void setIsControlFrame(bool);
    bool getIsControlFrame();

    void setReservedFlag1(bool);
    bool getReservedFlag1();

    void setReservedFlag2(bool);
    bool getReservedFlag2();

    void setReservedFlag3(bool);
    bool getReservedFlag3();

    void setMasked(bool);
    bool getMasked();

    void setFrameLength(long);
    long getFrameLength();

    void setMaskKey(ByteArray);
    ByteArray getMaskKey();

    int getHeadSize();
    void setHeadSize(int);

    void setB0(int b0);
    void setB1(int b1);

    int getB0();
    int getB1();
    
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
    _WebSocketFrame();
    
    void setHeader(WebSocketHeader);
    void setData(ByteArray data);

    WebSocketHeader getHeader();
    ByteArray getData();

    int getCloseStatus();
    void setCloseStatus(int);

private:
    WebSocketHeader mHeader;
    ByteArray mData; 
    int mCloseStatus;
};

}
#endif