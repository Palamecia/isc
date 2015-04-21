#include "nulldescriptor.h"
#include "nullvalue.h"

ISCValuePtr NullDescriptor::m_null = NullValuePtr(new NullValue);
ISCObject* NullDescriptor::m_instance = NULL;
NullDescriptor* NullDescriptor::m_singleton = new NullDescriptor;

NullDescriptor::NullDescriptor() : TypeDescriptor(null_key_word) {
    m_instance = new ISCObject(this, null_key_word);
    createInstance(NULL, ISCObjectList(), ISCObject::ExternAcces | ISCObject::ChildAcces, m_instance);
}

void NullDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    instance->init(m_null.get(), accesMask);
}

ISCObject* NullDescriptor::instance() {
    return m_instance;
}
