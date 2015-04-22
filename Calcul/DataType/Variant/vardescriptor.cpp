#include "vardescriptor.h"
#include "Calcul/DataType/None/voiddescriptor.h"

VarDescriptor::VarDescriptor() : TypeDescriptor(var_key_word) {
    TypeDescriptor::BuiltIn[var_type] = this;
}

void VarDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    instance->init(VoidDescriptor::instance()->value().get(), accesMask);
}
