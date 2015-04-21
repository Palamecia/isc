#include "nullvalue.h"
#include "System/errormanager.h"

NullValue::NullValue() : BuiltinValue(NULL)
{}

TypeInfo NullValue::typeInfo() {
    return void_type;
}

ISCObject* NullValue::get(ISCObject*, const String&) {
    raise_error(NULL_PTR);
    return NULL;
}

ISCObject* NullValue::call(ISCObject *requester, ISCObject *self, const String &member, const ISCObjectList &args) {
    raise_error(NULL_PTR);
    return NULL;
}
