#include "string.h"
#include <cstdio>

String::String() : std::string()
{}

String::String(const String& str) : std::string(str)
{}

String::String(const std::string& str) : std::string(str)
{}

String::String(const char* s) : std::string(s)
{}

String::String(const char c) : std::string(1, c)
{}

String& String::format(const char *form, ...) {
    va_list arg;
    va_start(arg, form);
    char buff[1024];
    sprintf(buff, form, arg);
    *this = String(buff);
    return *this;
}

bool String::startsWith(const String& str) const {
    return !std::string::compare(0, str.size(), str);
}

bool String::endsWith(const String& str) const {
    return !(size() < str.size()) && !compare(size()-str.size(), str.size(), str);
}

bool String::isEmpty() const {
    return empty();
}

String& String::replace(const String& before, const String& after) {
    size_t pos = 0;
    while ((pos = find(before, pos)) != npos) {
        std::string::replace(pos, before.size(), after);
    }
    return *this;
}

StringList String::split(const String& sep, bool keepEmptyPart) const {
    StringList res;
    size_t beg = 0, pos = 0, sep_size = sep.size();
    while ((pos = std::string::find(sep, beg)) != npos) {
        String elt = substr(beg, pos-beg);
        if (!elt.empty() || keepEmptyPart) res.append(elt);
        beg = pos+sep_size;
    }
    String elt = substr(beg);
    if (!elt.empty() || keepEmptyPart) res.append(elt);
    return res;
}

String& String::operator =(const std::string& other) {
    return *this = String(other);
}

bool String::operator ==(const char c) const {
    return *this == String(c);
}

int String::toInt(bool *good, int base) const {
    int res = 0;
    for (std::string::const_iterator it = begin(); it != end(); ++it) {
        if (*it < '0' || *it > '9') {
            if (good) *good = false;
            return 0;
        }
        res *= base;
        res += *it - '0';
    }
    if (good) *good = true;
    return res;
}

String StringList::join(const String& sep) const {
    String result;
    if (!empty()) result = at(0);
    for (uint i = 1; i < size(); ++i) {
        result += sep + at(i);
    }
    return result;
}
