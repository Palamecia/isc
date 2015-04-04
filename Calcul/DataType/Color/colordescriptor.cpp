#include "colordescriptor.h"

ColorDescriptor::ColorDescriptor() : TypeDescriptor(color_key_word) {
    TypeDescriptor::BuiltIn[color_type] = this;
}

void ColorDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {

}
