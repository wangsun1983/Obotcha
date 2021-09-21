#include <iostream>

#include "PrintStream.hpp"

namespace obotcha {

_PrintStream::_PrintStream(File file) {
    mPath = file->getAbsolutePath();
    isDefaultOut = false;
}

_PrintStream::_PrintStream(String path) {
    mPath = path;
    isDefaultOut = false;
}

_PrintStream::_PrintStream() { isDefaultOut = true; }

void _PrintStream::setOutPath(String path) {
    // Thread security,TODO
    mPath = path;
    isDefaultOut = false;
}

long _PrintStream::write(char c) {
    if (isDefaultOut) {
        fstream << c;
    } else {
        std::cout << c;
    }

    return 1;
}

long _PrintStream::write(ByteArray buff, long size) {
    if (size > buff->size()) {
        size = buff->size();
    }

    if (isDefaultOut) {
        fstream.write((char *)buff->toValue(), size);
    } else {
        std::cout.write((char *)buff->toValue(), size);
    }
    return size;
}

long _PrintStream::write(ByteArray buffer) {
    return write(buffer, buffer->size());
}

void _PrintStream::println(String s) {
    if (isDefaultOut) {
        std::cout << s->toChars();
        std::cout << std::endl;
    } else {
        fstream << s->toChars();
        fstream << std::endl;
    }
}

void _PrintStream::print(String s) {
    if (isDefaultOut) {
        std::cout << s->toChars();
    } else {
        fstream << s->toChars();
    }
}

void _PrintStream::newline() {
    if (isDefaultOut) {
        std::cout << std::endl;
    } else {
        fstream << std::endl;
    }
}

bool _PrintStream::open() {
    if (!isDefaultOut) {
        fstream.open(mPath->toChars(), std::ios::app);
        return fstream.is_open();
    }

    return true;
}

void _PrintStream::close() {
    if (!isDefaultOut) {
        fstream.close();
    }
}

void _PrintStream::flush() {
    if (!isDefaultOut) {
        fstream.flush();
    }
}

} // namespace obotcha