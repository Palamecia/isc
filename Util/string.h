#ifndef STRING_H
#define STRING_H

#include "typedefs.h"
#include <string>
#include <stdarg.h>

class StringList;

class String : public std::string {
public:
    String();
    String(const String& str);
    String(const std::string& str);
    String(const char* s);
    String(const char c);

    String &format(const char *form, ...);

    bool startsWith(const String& str) const;
    bool endsWith(const String& str) const;
    bool isEmpty() const;

    String& replace(const String& before, const String& after);
    StringList split(const String& sep, bool keepEmptyPart = true) const;

    String& operator =(const std::string& other);
    bool operator ==(const char c) const;

    int toInt(bool *good = 0, int base = 10) const;
};

#include "list.h"
class StringList : public List<String> {
public:
    inline StringList &operator<<(const String &str)
    { append(str); return *this; }

    String join(const String& sep = String()) const;
};

#endif // STRING_H
