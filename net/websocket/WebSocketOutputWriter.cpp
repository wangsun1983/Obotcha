#include "WebSocketOutputWriter.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "Log.hpp"
#include "ProtocolNotSupportException.hpp"
#include "ForEveryOne.hpp"

namespace obotcha {

_WebSocketOutputWriter::_WebSocketOutputWriter(int version,
                                               _WebSocketProtocol::Model model,
                                               Socket sock):mSocket(sock) {
    mOutputStream = sock->getOutputStream();
    switch (version) {
        case 0: {
            mComposer = WebSocketHybi00Composer::New(model);
        } break;

        case 7: {
            mComposer = WebSocketHybi07Composer::New(model);
        } break;

        case 8: {
            mComposer = WebSocketHybi08Composer::New(model);
        } break;

        case 13: {
            mComposer = WebSocketHybi13Composer::New(model);
        } break;

        default:
            LOG(ERROR)<<"WebSocket OutputWriter Protocol Not Support,Version is "<<version;
        break;
    }
}

void _WebSocketOutputWriter::setDeflate(WebSocketPermessageDeflate deflate) {
    mComposer->setDeflate(deflate);
}

long _WebSocketOutputWriter::sendTextMessage(String data) {
    return this->send(st(WebSocketProtocol)::OPCODE_TEXT, data->toByteArray());
}

long _WebSocketOutputWriter::sendBinaryMessage(ByteArray data) {
    return this->send(st(WebSocketProtocol)::OPCODE_BINARY, data);
}

long _WebSocketOutputWriter::sendPingMessage(ByteArray data) {
    return this->send(st(WebSocketProtocol)::OPCODE_CONTROL_PING, data);
}

long _WebSocketOutputWriter::sendPongMessage(ByteArray data) {
    return this->send(st(WebSocketProtocol)::OPCODE_CONTROL_PONG, data);
}

long _WebSocketOutputWriter::sendCloseMessage(int status,ByteArray extraInfo) {
    ByteArray data = ByteArray::New(2);
    data[0] = status/256;
    data[1] = status%256;

    if(extraInfo != nullptr) {
        data->append(extraInfo);
    }
    
    return send(st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE, data);
}

long _WebSocketOutputWriter::send(int type, ByteArray msg) {
    long size = 0;
    ArrayList<ByteArray> datas = nullptr;

    switch (type) {
        case st(WebSocketProtocol)::OPCODE_TEXT:
            datas = mComposer->genTextMessage(msg->toString());
            break;

        case st(WebSocketProtocol)::OPCODE_BINARY:
            datas = mComposer->genBinaryMessage(msg);
            break;

        case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
            datas = ArrayList<ByteArray>::New();
            datas->add(mComposer->genCloseMessage(msg->toString()));
            break;

        case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
            datas = ArrayList<ByteArray>::New();
            datas->add(mComposer->genPingMessage(msg->toString()));
            break;

        case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
            datas = ArrayList<ByteArray>::New();
            datas->add(mComposer->genPongMessage(msg->toString()));
            break;

        default:
            Trigger(ProtocolNotSupportException,"WebSocketLinker not support OPCODE")
    }

    ForEveryOne(data,datas) {
        size += mOutputStream->write(data);
    }

    return size;
}


}

