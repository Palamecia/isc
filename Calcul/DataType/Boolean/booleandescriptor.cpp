#include "booleandescriptor.h"
#include "booleanvalue.h"

BooleanDescriptor::BooleanDescriptor() : TypeDescriptor(bool_key_word) {
    TypeDescriptor::BuiltIn[bool_type] = this;
}

void BooleanDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {

}

BooleanValue* BooleanDescriptor::makeValue(const String& raw) {
    BooleanValue* value = NULL;
    if (raw == true_key_word) {
        value = new BooleanValue(true);
        //value->setFunctionMapping(m_fcts);
    }
    if (raw == false_key_word) {
        value = new BooleanValue(false);
        //value->setFunctionMapping(m_fcts);
    }
    return value;
}

BooleanValue* BooleanDescriptor::fromData(bool data) {
    BooleanValue* value = new BooleanValue(data);
    //value->setFunctionMapping(m_fcts);
    return value;
}
