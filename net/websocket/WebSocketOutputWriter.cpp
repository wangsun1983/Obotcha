#include "WebSocketOutputWriter.hpp"
#include "WebSocketProtocol.hpp"
#include "WebSocketHybi00Composer.hpp"
#include "WebSocketHybi07Composer.hpp"
#include "WebSocketHybi08Composer.hpp"
#include "WebSocketHybi13Composer.hpp"
#include "Log.hpp"
#include "ProtocolNotSupportException.hpp"

namespace obotcha {

_WebSocketOutputWriter::_WebSocketOutputWriter(int version,int type,Socket sock) {
    mSocket = sock;
    mOutputStream = sock->getOutputStream();

    switch (version) {
        case 0: {
            mComposer = createWebSocketHybi00Composer(type);
            break;
        }

        case 7: {
            mComposer = createWebSocketHybi07Composer(type);
            break;
        }

        case 8: {
            mComposer = createWebSocketHybi08Composer(type);
            break;
        }

        case 13: {
            mComposer = createWebSocketHybi13Composer(type);
            break;
        }

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
    ByteArray data = createByteArray(2);
    data[0] = status/256;
    data[1] = status%256;

    if(extraInfo != nullptr) {
        data->append(extraInfo);
    }
    
    return send(st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE, data);
}

long _WebSocketOutputWriter::send(int type, ByteArray msg) {
    if (mOutputStream != nullptr) {
        long size = 0;
        ArrayList<ByteArray> data = nullptr;

        switch (type) {
            case st(WebSocketProtocol)::OPCODE_TEXT:
                data = mComposer->genTextMessage(msg->toString());
                break;

            case st(WebSocketProtocol)::OPCODE_BINARY:
                data = mComposer->genBinaryMessage(msg);
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_CLOSE:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genCloseMessage(msg->toString()));
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_PING:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPingMessage(msg->toString()));
                break;

            case st(WebSocketProtocol)::OPCODE_CONTROL_PONG:
                data = createArrayList<ByteArray>();
                data->add(mComposer->genPongMessage(msg->toString()));
                break;

            default:
                Trigger(ProtocolNotSupportException,"WebSocketLinker not support OPCODE");
        }

        ListIterator<ByteArray> iterator = data->getIterator();
        while (iterator->hasValue()) {
            ByteArray sendData = iterator->getValue();
            size += mOutputStream->write(sendData);
            iterator->next();
        }

        return size;
    }

    return -1;
}


}
