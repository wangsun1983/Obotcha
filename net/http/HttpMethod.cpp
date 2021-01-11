#include "HttpMethod.hpp"

namespace obotcha {

const String _HttpMethod::GetMethodString = createString("GET");
const String _HttpMethod::DeleteMethodString = createString("DELETE");
const String _HttpMethod::PostMethodString = createString("POST");
const String _HttpMethod::PutMethodString = createString("PUT");

String _HttpMethod::toString(int method) {
    switch(method) {
        case Get:
        return GetMethodString;

        case Delete:
        return DeleteMethodString;

        case Post:
        return PostMethodString;

        case Put:
        return PutMethodString;
    }

    return nullptr;
}


}