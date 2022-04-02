#include "ConfReader.hpp"
#include "Error.hpp"
#include "InitializeException.hpp"

extern "C" {
#include "ccl.h"
}

namespace obotcha {

_ConfReader::_ConfReader(const char *path) : _ConfReader(createFile(path)) {}

_ConfReader::_ConfReader(String path) : _ConfReader(createFile(path)) {}

_ConfReader::_ConfReader(File file) {
    mConfFile = file;
    if (!mConfFile->exists()) {
        Trigger(InitializeException, "File Not Exist");
    }

    parse();
}

int _ConfReader::parse() {
    if (!mConfFile->exists()) {
        return -ENOENT;
    }

    config.comment_char = '#';
    config.sep_char = '=';
    config.str_char = '"';

    if (0 == ccl_parse(&config,
                       (const char *)mConfFile->getAbsolutePath()->toChars())) {
        return 0;
    }

    return -1;
}

_ConfReader::~_ConfReader() {
    ccl_release(&config);
}

sp<_ConfIterator> _ConfReader::getIterator() {
    return createConfIterator(AutoClone(this));
}

String _ConfReader::get(String tag) {
    const char *value = ccl_get(&config, (const char *)tag->toChars());
    if (value == nullptr || value[0] == 0) {
        return nullptr;
    }

    return createString(value);
}

//-------------iterator-------------
_ConfIterator::_ConfIterator(ConfReader v) {
    reader = v;
    ccl_t *pair = &(v->config);
    ccl_reset(pair);
    iterator = (ccl_pair_t *)ccl_iterate(pair);
}

String _ConfIterator::getTag() {
    if (iterator != nullptr) {
        return createString(iterator->key);
    }

    return nullptr;
}

String _ConfIterator::getValue() {
    if (iterator != nullptr) {
        return createString(iterator->value);
    }

    return nullptr;
}

bool _ConfIterator::hasValue() { 
    return iterator != nullptr; 
}

bool _ConfIterator::next() {
    ccl_t *pair = &(reader->config);
    iterator = (ccl_pair_t *)ccl_iterate(pair);
    return (iterator != nullptr);
}

} // namespace obotcha