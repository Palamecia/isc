#include "builtinfunction.h"

BuiltinFunction::BuiltinFunction()
{}

BuiltinFunction::~BuiltinFunction() {
    for (uint i = 0; i < m_shapes.size(); ++i) {
        delete [] m_shapes[i].pt;
    }
}

ISCObject* BuiltinFunction::run(ISCObject* self, const ISCObjectList& params) {
    for (uint i = 0 ; i < m_shapes.size(); ++i) {
        if (m_shapes[i].pc == params.size()) {
            bool good = true;
            for (uint p = 0; p < params.size(); ++p) {
                if (!params[p]->instanceOf(*m_shapes[i].pt[p]) || !!params[p]->inheritFrom(*m_shapes[i].pt[p])) {
                    good = false;
                }
            }
            if (good) return (*m_shapes[i].code)(self, params);
        }
    }
    return NULL;
}
