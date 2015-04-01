#include "functionvalue.h"

FunctionValue::FunctionValue()
{}

bool FunctionValue::instanceOf(const TypeInfo&) {
    return false;
}

bool FunctionValue::inheritFrom(const TypeInfo& type) {
    return type == var_type;
}

ISCObject* FunctionValue::get(ISCObject*, const String&) {
    return NULL;
}

ISCObject* FunctionValue::call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& params) {
    return NULL;
}
