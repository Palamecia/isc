#include "builtinfunction.h"

BuiltinFunction::BuiltinFunction()
{}

BuiltinFunction::~BuiltinFunction() {
    for (uint i = 0; i < m_shapes.size(); ++i) {
        delete [] m_shapes[i].pt;
    }
}

ISCObject* BuiltinFunction::run(ISCObject* self, const ISCObjectList& args) {
    for (uint i = 0 ; i < m_shapes.size(); ++i) {
        if (m_shapes[i].pc == args.size()) {
            bool good = true;
            for (uint p = 0; p < args.size(); ++p) {
                if (!args[p]->instanceOf(*m_shapes[i].pt[p]) || !!args[p]->inheritFrom(*m_shapes[i].pt[p])) {
                    good = false;
                }
            }
            if (good) return (*m_shapes[i].code)(self, args);
        }
    }
    return NULL;
}
