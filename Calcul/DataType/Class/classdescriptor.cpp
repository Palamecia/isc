#include "classdescriptor.h"
#include "Calcul/iscobject.h"
#include "Calcul/DataType/objectdescriptor.h"
#include "System/errormanager.h"
#include "uservalue.h"

ClassDescriptor::ClassDescriptor(const String &name) : TypeDescriptor(name)
{}

ClassDescriptor::~ClassDescriptor() {
    for (MemberMap::iterator it =  m_members.begin(); it != m_members.end(); ++it) {
        delete it->second;
    }
}

TypeDescriptor* ClassDescriptor::getType(const String& type) {
    MemberMap::iterator it = m_members.find(type);
    if (it == m_members.end()) return NULL;
    return dynamic_cast<TypeDescriptor*>(it->second);
}

void ClassDescriptor::createInstance(ProcessManager* process, const ISCObjectList& args, byte accesMask, ISCObject* instance) {
    UserValue* value = new UserValue(this);
    for (MemberMap::iterator it =  m_members.begin(); it != m_members.end(); ++it) {
        if (ObjectDescriptor* desc = dynamic_cast<ObjectDescriptor*>(it->second)) {
            if (!(desc->accesMask() & ISCObject::StaticAcces)) { // static members are already created
                ISCObject * object = desc->newObject();
                desc->createInstance(process, ISCObjectList(), byte(), object);
                value->addMember(object);
            }
        }
    }
    instance->init(value, accesMask);
    instance->call(instance, new_operator, args);
}

void ClassDescriptor::declareParent(TypeDescriptor * parent) {

}

void ClassDescriptor::declareType(TypeDescriptor * type) {
    if (!m_members.insert(MemberMap::value_type(type->name(), type)).second) {
        raise_error(TYPE_DUPLICATION, m_name.c_str(), type->name().c_str());
    }
}

void ClassDescriptor::declareMember(ObjectDescriptor * object) {
    if (!m_members.insert(MemberMap::value_type(object->name(), object)).second) {
        raise_error(MEMBER_DUPLICATION, m_name.c_str(), object->name().c_str());
    }
}
