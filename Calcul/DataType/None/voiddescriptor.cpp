#include "voiddescriptor.h"
#include "voidvalue.h"

ISCValuePtr VoidDescriptor::m_none = VoidValuePtr(new VoidValue);
ISCObject* VoidDescriptor::m_instance = NULL;

VoidDescriptor::VoidDescriptor() : TypeDescriptor(void_key_word) {
    TypeDescriptor::BuiltIn[void_type] = this;
    m_instance = new ISCObject(this, none_key_word);
    createInstance(NULL, ISCObjectList(), ISCObject::ExternAcces | ISCObject::ChildAcces, m_instance);
}

bool VoidDescriptor::extend(const TypeDescriptor &) const {
    return true;
}

void VoidDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    instance->init(m_none.get(), accesMask);
}

ISCObject* VoidDescriptor::instance() {
    return m_instance;
}
