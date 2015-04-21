#include "uservalue.h"
#include "Calcul/DataType/Function/functionvalue.h"

UserValue::UserValue(ClassDescriptor* typeId)
    : m_typeId(typeId)
{}

TypeInfo UserValue::typeInfo() {
    return m_typeId;
}

ISCObject *UserValue::get(ISCObject *requester, const String& member) {
    ISCObjectMapping::iterator it = m_members.find(member);
    if (it != m_members.end()) {
        return it->second;
    }

    for (it = m_vtable.begin(); it != m_vtable.end(); ++it) {
        ISCObject* ret = it->second->get(requester, member);
        if (ret) return ret;
    }

    return NULL;
}

ISCObject *UserValue::call(ISCObject *requester, ISCObject *self, const String& member, const ISCObjectList& args) {
    ISCObject* ret = NULL;
    ISCObjectMapping::iterator it = m_members.find(member);
    if (it != m_members.end()) {
        // tester visibilitée it->seconde pour requester

        FunctionValuePtr fct = std::tr1::dynamic_pointer_cast<FunctionValue>(it->second->value());

        ret = fct->run(self, args);
        if (ret) return ret;
    }

    for (it = m_vtable.begin(); it != m_vtable.end(); ++it) {
        // cast parent
        if (it->first == member) return it->second;

        // methodes héritées
        ret = it->second->call(requester, member, args);
        if (ret) return ret;
    }

    return NULL;
}

void UserValue::addMember(ISCObject* object) {
    m_members.insert(ISCObjectMapping::value_type(object->name(), object));
}
