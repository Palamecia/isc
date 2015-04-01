#ifndef MODULE_H
#define MODULE_H

#include "iscparser.h"

class Module {
public:
    Module();
    Module(const String &name);
    Module(const String &name, ISCSI* input);

    String name();
    Step* step(pos_t idx, Dictionary* dico);
    uint line(pos_t idx);
    String raw(pos_t idx);

private:
    String      m_name;
    ISCParser   m_parser;
};

#endif // MODULE_H
