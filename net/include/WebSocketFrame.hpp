#ifndef __OBOTCHA_WEB_SOCKET_FRAME_HPP__
#define __OBOTCHA_WEB_SOCKET_FRAME_HPP__

#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"

namespace obotcha {

DECLARE_SIMPLE_CLASS(WebSocketHeader) {
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
};

DECLARE_SIMPLE_CLASS(WebSocketFrame) {
public:
    _WebSocketFrame(WebSocketHeader,ByteArray);
    _WebSocketFrame();
    
    void setHeader(WebSocketHeader);
    void setData(ByteArray data);

    WebSocketHeader getHeader();
    ByteArray getData();

private:
    WebSocketHeader mHeader;
    String mMessage;
    ByteArray mData; 
};

}
#endif
