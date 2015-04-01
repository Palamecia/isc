#include "Calcul/DataType/builtinvalue.h"
#include "Calcul/DataType/Function/functionvalue.h"

BuiltinValue::BuiltinValue() {
}

ISCObject* BuiltinValue::call(ISCObject* requester, ISCObject *self, const String& member, const ISCObjectList& params) {
    ISCObjectMapping::iterator it = m_fcts->find(member);
    if (it == m_fcts->end()) {
        // TODO : Errer
    }
    FunctionValuePtr fct = std::tr1::dynamic_pointer_cast<FunctionValue>(it->second->value());
    ISCObject* ret = fct->run(self, params);
    if (!ret) {
        // TODO : Erreur
    }
    return ret;
}

void BuiltinValue::setFunctionMapping(ISCObjectMapping *mapping) {
    m_fcts = mapping;
}
