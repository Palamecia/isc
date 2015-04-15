#include "integervalue.h"

IntegerValue::IntegerValue(ISCObjectMapping *fcts, const int value) : BuiltinValue(fcts), m_value(value)
{}

bool IntegerValue::instanceOf(const TypeInfo& type) {
    return type == int_type;
}

int &IntegerValue::toInt() {
    return m_value;
}
