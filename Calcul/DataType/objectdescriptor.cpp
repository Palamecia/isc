#include "objectdescriptor.h"

ObjectDescriptor::ObjectDescriptor(byte accesMask, const TypeInfo& type, const String& name)
    : m_accesMask(accesMask),
      m_typeInfo(type),
      MemberDescriptor(name)
{}

ISCObject* ObjectDescriptor::newObject() {
    return new ISCObject(m_typeInfo, m_name);
}

void ObjectDescriptor::createInstance(ProcessManager* process, const ISCObjectList& args, byte accesMask, ISCObject* instance) {
    byte protectedMask = m_accesMask | accesMask;
    m_typeInfo.createInstance(process, args, protectedMask, instance);
}

byte ObjectDescriptor::accesMask() {
    return m_accesMask;
}
