#include "floatdescriptor.h"

FloatDescriptor::FloatDescriptor() : TypeDescriptor(float_key_word) {
    TypeDescriptor::BuiltIn[float_type] = this;
}

void FloatDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {

}
