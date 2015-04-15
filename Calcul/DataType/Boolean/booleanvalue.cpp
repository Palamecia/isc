#include "booleanvalue.h"

BooleanValue::BooleanValue(ISCObjectMapping *fcts, bool value) : BuiltinValue(fcts), m_value(value)
{}

bool BooleanValue::instanceOf(const TypeInfo& type) {
    return type == bool_type;
}

ISCObject* BooleanValue::get(ISCObject* requester, const String& member) {
    return NULL;
}

ISCObject* BooleanValue::call(ISCObject* requester, const String& member, const ISCObjectList& args) {
    return NULL;
}

bool &BooleanValue::toBool() {
    return m_value;
}
