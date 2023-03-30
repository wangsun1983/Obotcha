#include "WebSocketFrame.hpp"

namespace obotcha {

//------------WebSocketHeader------------
_WebSocketHeader::_WebSocketHeader() {
    clear();
}

void _WebSocketHeader::clear() {
    mOpcode = mFrameLength = -1;
    mIsFinalFrame = mIsControlFrame = mReservedFlag1 = mReservedFlag2 = mReservedFlag3 = mIsMasked = false;
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

void _WebSocketHeader::setB0(int b0) {
    mB0 = b0;
}

void _WebSocketHeader::setB1(int b1) {
    mB1 = b1;
}

int _WebSocketHeader::getB0() {
    return mB0;
}

int _WebSocketHeader::getB1() {
    return mB1;
}

//------------WebSocketFrame------------
_WebSocketFrame::_WebSocketFrame() {
    mHeader = nullptr;
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

int _WebSocketFrame::getCloseStatus() {
    return mCloseStatus;
}

void _WebSocketFrame::setCloseStatus(int status) {
    mCloseStatus = status;
}

}

