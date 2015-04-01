#include "voidvalue.h"

VoidValue::VoidValue()
{}

bool VoidValue::inheritFrom(const TypeInfo &) {
    return true;
}

bool VoidValue::instanceOf(const TypeInfo &type) {
    return type == void_type;
}

ISCObject* VoidValue::get(ISCObject*, const String&) {
    return NULL;
}
