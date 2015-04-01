#include "voiddescriptor.h"
#include "voidvalue.h"

ISCObject* VoidDescriptor::m_noneObject = NULL;

VoidDescriptor::VoidDescriptor() : TypeDescriptor(void_key_word) {
    TypeDescriptor::BuiltIn[void_type] = this;
    VoidDescriptor::m_noneObject = new ISCObject(this, none_key_word);
    VoidDescriptor::m_noneObject->init(new VoidValue, ISCObject::ExternAcces | ISCObject::ChildAcces | ISCObject::ConstRefAcces);
}

void VoidDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance) {
    *instance = *VoidDescriptor::m_noneObject;
}
