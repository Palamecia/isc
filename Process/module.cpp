#include "module.h"

Module::Module()
    : m_name("stdin")
{}

Module::Module(const String& name)
    : m_name(name),
    m_parser(name)
{}

Module::Module(const String& name, ISCSI* input)
    : m_name(name),
    m_parser(input)
{}

String Module::name() {
    return m_name;
}

Step* Module::step(pos_t idx, Dictionary *dico) {
    return m_parser.step(idx, dico);
}

uint Module::line(pos_t idx) {
    return m_parser.line(idx);
}

String Module::raw(pos_t idx) {
    return m_parser.raw(idx);
}
