#include "errordescriptor.h"
#include "errorvalue.h"

ISCObjectMapping* ErrorDescriptor::m_fcts = new ISCObjectMapping;

ErrorDescriptor::ErrorDescriptor() : TypeDescriptor(error_key_word) {
    TypeDescriptor::BuiltIn[error_type] = this;
}

void ErrorDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    ErrorValue* value = new ErrorValue(m_fcts);
    instance->init(value, accesMask);
}

ErrorValue *ErrorDescriptor::makeValue(const String& raw) {
    return fromData(raw);
}

ErrorValue* ErrorDescriptor::fromData(const String& data) {
    ErrorValue *value = new ErrorValue(m_fcts, data);
    return value;
}
