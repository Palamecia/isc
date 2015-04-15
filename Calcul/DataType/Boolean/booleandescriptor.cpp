#include "booleandescriptor.h"
#include "booleanvalue.h"

ISCObjectMapping* BooleanDescriptor::m_fcts = new ISCObjectMapping;

BooleanDescriptor::BooleanDescriptor() : TypeDescriptor(bool_key_word) {
    TypeDescriptor::BuiltIn[bool_type] = this;
}

void BooleanDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    BooleanValue* value = new BooleanValue(m_fcts);
    instance->init(value, accesMask);
}

BooleanValue* BooleanDescriptor::makeValue(const String& raw) {
    BooleanValue* value = NULL;
    if (raw == true_key_word) {
        value = new BooleanValue(m_fcts, true);
    }
    if (raw == false_key_word) {
        value = new BooleanValue(m_fcts, false);
    }
    return value;
}

BooleanValue* BooleanDescriptor::fromData(bool data) {
    BooleanValue* value = new BooleanValue(m_fcts, data);
    return value;
}
