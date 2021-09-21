#include "HttpSession.hpp"

namespace obotcha {

_HttpSession::_HttpSession() { data = createHashMap<String, String>(); }

String _HttpSession::get(String key) { return data->get(key); }

void _HttpSession::set(String key, String value) { data->put(key, value); }

} // namespace obotcha