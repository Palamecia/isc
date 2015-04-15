#include "stringdescriptor.h"
#include "stringvalue.h"

ISCObjectMapping* StringDescriptor::m_fcts = new ISCObjectMapping;

StringDescriptor::StringDescriptor() : TypeDescriptor(string_key_word) {
    TypeDescriptor::BuiltIn[string_type] = this;
}

void StringDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    StringValue* value = new StringValue(m_fcts);
    instance->init(value, accesMask);
}

StringValue* StringDescriptor::makeValue(const String& raw) {
    if ((raw.startsWith("'") && raw.endsWith("'")) || (raw.startsWith("\"") && raw.endsWith("\""))) {
        String stringValue = raw.substr(1, raw.size() - 2);
        stringValue.replace("\\t", "\t");
        stringValue.replace("\\n", "\n");
        // ...
        StringValue* value = new StringValue(m_fcts, stringValue);
        // value->setFunctionMapping(m_fcts);
        return value;
    }
    return NULL;
}
