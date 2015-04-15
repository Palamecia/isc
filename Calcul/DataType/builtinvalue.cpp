#include "Calcul/DataType/builtinvalue.h"
#include "Calcul/DataType/Function/functionvalue.h"

BuiltinValue::BuiltinValue(ISCObjectMapping *fcts)
    : m_fcts(fcts)
{}

ISCObject* BuiltinValue::get(ISCObject *requester, const String &member) {
    ISCObjectMapping::iterator it = m_fcts->find(member);
    if (it != m_fcts->end()) {
        return it->second;
    }
    return NULL;
}

ISCObject* BuiltinValue::call(ISCObject* requester, ISCObject *self, const String& member, const ISCObjectList& args) {
    ISCObjectMapping::iterator it = m_fcts->find(member);
    if (it == m_fcts->end()) {
        // TODO : Errer
    }
    FunctionValuePtr fct = std::tr1::dynamic_pointer_cast<FunctionValue>(it->second->value());
    ISCObject* ret = fct->run(self, args);
    if (!ret) {
        // TODO : Erreur
    }
    return ret;
}
