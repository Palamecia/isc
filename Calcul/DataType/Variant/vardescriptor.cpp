#include "vardescriptor.h"

VarDescriptor::VarDescriptor() : TypeDescriptor(var_key_word) {
    TypeDescriptor::BuiltIn[var_type] = this;
}

void VarDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {

}
