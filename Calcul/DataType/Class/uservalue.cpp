#include "uservalue.h"
#include "Calcul/DataType/Function/functionvalue.h"

UserValue::UserValue(ClassDescriptor* typeId)
    : m_typeId(typeId)
{}

bool UserValue::instanceOf(const TypeInfo& type) {
    return type.descriptor() == m_typeId && type.modifiers().isEmpty();
}

bool UserValue::inheritFrom(const TypeInfo& type) {
    ISCObjectMapping::iterator it;
    for (it = m_vtable.begin(); it != m_vtable.end(); ++it) {
        if (it->second->instanceOf(type)) return true;
        if (it->second->inheritFrom(type)) return true;
    }
    return ISCValue::inheritFrom(type);
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

ISCObject *UserValue::call(ISCObject *requester, ISCObject *self, const String& member, const ISCObjectList& params) {
    ISCObject* ret = NULL;
    ISCObjectMapping::iterator it = m_members.find(member);
    if (it != m_members.end()) {
        // tester visibilitée it->seconde pour requester

        FunctionValuePtr fct = std::tr1::dynamic_pointer_cast<FunctionValue>(it->second->value());

        ret = fct->run(self, params);
        if (ret) return ret;
    }

    for (it = m_vtable.begin(); it != m_vtable.end(); ++it) {
        // cast parent
        if (it->first == member) return it->second;

        // methodes héritées
        ret = it->second->call(requester, member, params);
        if (ret) return ret;
    }

    return NULL;
}

void UserValue::addMember(ISCObject* object) {
    m_members.insert(ISCObjectMapping::value_type(object->name(), object));
}
