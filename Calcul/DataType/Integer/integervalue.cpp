#include "integervalue.h"

IntegerValue::IntegerValue(const int value) : m_value(value)
{}

bool IntegerValue::instanceOf(const TypeInfo& type) {
    return type == int_type;
}

ISCObject* IntegerValue::get(ISCObject* requester, const String& member) {
    return NULL;
}

int &IntegerValue::toInt() {
    return m_value;
}
