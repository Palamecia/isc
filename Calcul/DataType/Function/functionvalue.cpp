#include "functionvalue.h"

FunctionValue::FunctionValue()
{}

TypeInfo FunctionValue::typeInfo() {
    return var_type;
}

ISCObject* FunctionValue::get(ISCObject*, const String&) {
    return NULL;
}

ISCObject* FunctionValue::call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& args) {
    return NULL;
}
