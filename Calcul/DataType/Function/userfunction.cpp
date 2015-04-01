#include "userfunction.h"
#include "Calcul/iscobject.h"
#include "Process/processmanager.h"

UserFunction::UserFunction(ProcessManager *process)
    : m_process(process)
{}

UserFunction::~UserFunction() {
    for (uint i = 0; i < m_shapes.size(); ++i) {
        delete [] m_shapes[i].pt;
    }
}

ISCObject* UserFunction::run(ISCObject* self, const ISCObjectList& params) {
    for (uint i = 0 ; i < m_shapes.size(); ++i) {
        if (m_shapes[i].pc == params.size()) {
            bool good = true;
            for (uint p = 0; p < params.size(); ++p) {
                if (!params[p]->instanceOf(m_shapes[i].pt[p]) || !!params[p]->inheritFrom(m_shapes[i].pt[p])) {
                    good = false;
                }
            }
            if (good) return m_process->call(m_shapes[i].module, m_shapes[i].pos, self, params);
        }
    }
    return NULL;
}
