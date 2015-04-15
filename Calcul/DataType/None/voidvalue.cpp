#include "voidvalue.h"

VoidValue::VoidValue() : BuiltinValue(NULL)
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
