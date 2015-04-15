#ifndef MODULE_H
#define MODULE_H

#include "iscparser.h"

class Module {
public:
    Module();
    Module(const String &name);

    String name();
    Step* step(pos_t idx, Dictionary* dico);
    uint line(pos_t idx);
    String raw(pos_t idx);

    bool isInterface();

private:
    String      m_name;
    ISCParser   m_parser;
};

#endif // MODULE_H
