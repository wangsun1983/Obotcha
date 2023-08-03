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

int _WebSocketHeader::getOpCode() const {
    return mOpcode;
}

void _WebSocketHeader::setIsFinalFrame(bool v) {
    mIsFinalFrame = v;
}
    
bool _WebSocketHeader::isFinalFrame() const {
    return mIsFinalFrame;
}

void _WebSocketHeader::setIsControlFrame(bool v) {
    mIsControlFrame = v;
}

bool _WebSocketHeader::getIsControlFrame() const {
    return mIsControlFrame;
}

void _WebSocketHeader::setReservedFlag1(bool v) {
    mReservedFlag1 = v;
}

bool _WebSocketHeader::getReservedFlag1() const {
    return mReservedFlag1;
}

void _WebSocketHeader::setReservedFlag2(bool v) {
    mReservedFlag2 = v;
}

bool _WebSocketHeader::getReservedFlag2() const {
    return mReservedFlag2;
}

void _WebSocketHeader::setReservedFlag3(bool v) {
    mReservedFlag3 = v;
}

bool _WebSocketHeader::getReservedFlag3() const {
    return mReservedFlag3;
}

void _WebSocketHeader::setMasked(bool v) {
    mIsMasked = v;
}
    
bool _WebSocketHeader::getMasked() const {
    return mIsMasked;
}

void _WebSocketHeader::setFrameLength(long v) {
    mFrameLength = v;
}

long _WebSocketHeader::getFrameLength() const {
    return mFrameLength;
}

void _WebSocketHeader::setMaskKey(ByteArray v) {
    mMaskKey = v;
}

ByteArray _WebSocketHeader::getMaskKey() const {
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

int _WebSocketHeader::getB0() const {
    return mB0;
}

int _WebSocketHeader::getB1() const {
    return mB1;
}

//------------WebSocketFrame------------
_WebSocketFrame::_WebSocketFrame(WebSocketHeader h,ByteArray d):mHeader(h),mData(d) {
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

