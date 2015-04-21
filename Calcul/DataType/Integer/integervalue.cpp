#include "integervalue.h"

IntegerValue::IntegerValue(ISCObjectMapping *fcts, const int value) : BuiltinValue(fcts), m_value(value)
{}

TypeInfo IntegerValue::typeInfo() {
    return int_type;
}

int &IntegerValue::toInt() {
    return m_value;
}
