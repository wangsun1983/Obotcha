#include "Object.hpp"
#include "StrongPointer.hpp"

#include "String.hpp"
#include "InetAddress.hpp"
#include "ByteArray.hpp"
#include "WebSocketFrame.hpp"

namespace obotcha {

//------------WebSocketHeader------------
_WebSocketHeader::_WebSocketHeader() {
    clear();
}

void _WebSocketHeader::clear() {
    mOpcode = -1;
    mIsFinalFrame = false;
    mIsControlFrame  = false;
    mReservedFlag1  = false;
    mReservedFlag2  = false;
    mReservedFlag3  = false;
    mIsMasked  = false;
    mFrameLength = -1;
    mMaskKey = nullptr;
    mHeadSize = 0;
}

void _WebSocketHeader::setOpCode(int v) {
    mOpcode = v;
}

int _WebSocketHeader::getOpCode() {
    return mOpcode;
}

void _WebSocketHeader::setIsFinalFrame(bool v) {
    mIsFinalFrame = v;
}
    
bool _WebSocketHeader::isFinalFrame() {
    return mIsFinalFrame;
}

void _WebSocketHeader::setIsControlFrame(bool v) {
    mIsControlFrame = v;
}

bool _WebSocketHeader::getIsControlFrame() {
    return mIsControlFrame;
}

void _WebSocketHeader::setReservedFlag1(bool v) {
    mReservedFlag1 = v;
}

bool _WebSocketHeader::getReservedFlag1() {
    return mReservedFlag1;
}

void _WebSocketHeader::setReservedFlag2(bool v) {
    mReservedFlag2 = v;
}

bool _WebSocketHeader::getReservedFlag2() {
    return mReservedFlag2;
}

void _WebSocketHeader::setReservedFlag3(bool v) {
    mReservedFlag3 = v;
}

bool _WebSocketHeader::getReservedFlag3() {
    return mReservedFlag3;
}

void _WebSocketHeader::setMasked(bool v) {
    mIsMasked = v;
}
    
bool _WebSocketHeader::getMasked() {
    return mIsMasked;
}

void _WebSocketHeader::setFrameLength(long v) {
    mFrameLength = v;
}

long _WebSocketHeader::getFrameLength() {
    return mFrameLength;
}

void _WebSocketHeader::setMaskKey(ByteArray v) {
    mMaskKey = v;
}

ByteArray _WebSocketHeader::getMaskKey() {
    return mMaskKey;
}

int _WebSocketHeader::getHeadSize() {
    return mHeadSize;
}

void _WebSocketHeader::setHeadSize(int v) {
    mHeadSize = v;
}

//------------WebSocketFrame------------
_WebSocketFrame::_WebSocketFrame() {
    mHeader = nullptr;
    mMessage = nullptr;
}

_WebSocketFrame::_WebSocketFrame(WebSocketHeader h,ByteArray d) {
    mHeader = h;
    mData = d;
}

void _WebSocketFrame::setHeader(WebSocketHeader h) {
    mHeader = h;
}

WebSocketHeader _WebSocketFrame::getHeader() {
    return mHeader;
}


void _WebSocketFrame::setData(ByteArray data) {
    mData = data;
}

ByteArray _WebSocketFrame::getData() {
    return mData;
}

}

