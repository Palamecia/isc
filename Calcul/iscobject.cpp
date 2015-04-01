#include "iscobject.h"
#include "Calcul/DataType/iscvalue.h"
#include "Calcul/DataType/typeinfo.h"

ISCObject::ISCObject(const TypeInfo& type, const String& name)
    : m_name(name),
    m_typeInfo(type),
    m_accesMask(ExternAcces | ChildAcces) {
    if (m_name.isEmpty()) m_name.format("@%p", this);
}

ISCObject::ISCObject(const ISCObject& other, const String& name)
    : m_name(name),
    m_typeInfo(other.m_typeInfo),
    m_value(other.m_value),
    m_accesMask(other.m_accesMask) {
    if (m_name.isEmpty()) m_name.format("@%p", this);
}

void ISCObject::construct(ProcessManager* process, const ISCObjectList& params) {
    m_typeInfo.createInstance(process, params, m_accesMask, this);
}

bool ISCObject::instanceOf(const TypeInfo& type) {
    return m_value->instanceOf(type);
}

bool ISCObject::inheritFrom(const TypeInfo& type) {
    return m_value->inheritFrom(type);
}

ISCObject *ISCObject::get(ISCObject *requester, const String& member) {
    return m_value->get(requester, member);
}

ISCObject *ISCObject::call(ISCObject *requester, const String& member, const ISCObjectList& params) {
    if (member == copy_operator) {
        if (params.size() != 1) {
            // TODO : Erreur
        }
        ISCObject* other = params.first();
        if (other->m_value->instanceOf(m_typeInfo) || other->m_value->inheritFrom(m_typeInfo)) {
            if (m_accesMask & ConstRefAcces || other->m_accesMask & ConstRefAcces) {
                return m_value->call(requester, this, deep_copy_operator, params);
            } else {
                m_value = other->m_value;
                return this;
            }
        } else {
            // TODO : Ereur
        }
    }
    else if (member == adress_operator) {

    }
    else if (member == const_ref_operator) {
        ISCObject * other = new ISCObject(*this);
        other->m_accesMask |= ConstRefAcces;
        return other;
    }
    return m_value->call(requester, this, member, params);
}

String &ISCObject::name() {
    return m_name;
}

ISCObject::ValuePtr ISCObject::value() {
    return m_value;
}

bool ISCObject::operator < (const ISCObject& other) const {
    return m_name < other.m_name;
}

void ISCObject::init(ISCValue* value, byte accesMask) {
    m_value = ValuePtr(value);
    m_accesMask = accesMask;
}