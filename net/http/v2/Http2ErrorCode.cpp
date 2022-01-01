#include "Object.hpp"
#include "StrongPointer.hpp"
#include "Http2ErrorCode.hpp"

namespace obotcha {

const int _Http2ErrorCode::NoError = 0x0;
const int _Http2ErrorCode::ProtocolError = 0x1;
const int _Http2ErrorCode::InternalError = 0x2;
const int _Http2ErrorCode::FlowControlError = 0x3;
const int _Http2ErrorCode::SettingTimeout = 0x4;
const int _Http2ErrorCode::StreamClosed = 0x5;
const int _Http2ErrorCode::FrameSizeError = 0x6;
const int _Http2ErrorCode::RefusedStream = 0x7;
const int _Http2ErrorCode::Cancel = 0x8;
const int _Http2ErrorCode::CompressionError = 0x9;
const int _Http2ErrorCode::ConnectError = 0xa;
const int _Http2ErrorCode::EnhanceYourCalm = 0xb;
const int _Http2ErrorCode::InadequateSecurity = 0xc;
const int _Http2ErrorCode::HttpV1Required = 0xd;

const String _Http2ErrorCode::NoErrorString = "No Error";
const String _Http2ErrorCode::ProtocolErrorString = "Protocol Error";
const String _Http2ErrorCode::InternalErrorString = "Internal Error";
const String _Http2ErrorCode::FlowControlErrorString = "Flow Control Error";
const String _Http2ErrorCode::SettingTimeoutString = "Setting Timeout";
const String _Http2ErrorCode::StreamClosedString = "Stream Closed";
const String _Http2ErrorCode::FrameSizeErrorString = "Frame Size Error";
const String _Http2ErrorCode::RefusedStreamString = "Refused Stream";
const String _Http2ErrorCode::CancelString = "Cancel";
const String _Http2ErrorCode::CompressionErrorString = "Compression Error";
const String _Http2ErrorCode::ConnectErrorString = "Connect Error";
const String _Http2ErrorCode::EnhanceYourCalmString = "Enhance Your Calm";
const String _Http2ErrorCode::InadequateSecurityString = "Inadequate Security";
const String _Http2ErrorCode::HttpV1RequiredString = "Http 1.1 Required";

String _Http2ErrorCode::toString(int code) {
    switch(code) {
        case NoError: return NoErrorString;
        case ProtocolError: return ProtocolErrorString;
        case InternalError: return InternalErrorString;
        case FlowControlError: return FlowControlErrorString;
        case SettingTimeout: return SettingTimeoutString;
        case StreamClosed: return StreamClosedString;
        case FrameSizeError: return FrameSizeErrorString;
        case RefusedStream: return RefusedStreamString;
        case Cancel: return CancelString;
        case CompressionError: return CompressionErrorString;
        case ConnectError: return ConnectErrorString;
        case EnhanceYourCalm: return EnhanceYourCalmString;
        case InadequateSecurity: return InadequateSecurityString;
        case HttpV1Required: return HttpV1RequiredString;
    }

    return nullptr;
}

}
