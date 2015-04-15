#include "errorvalue.h"

ErrorValue::ErrorValue(ISCObjectMapping *fcts, const String& value) : BuiltinValue(fcts), m_value(value)
{}

bool ErrorValue::instanceOf(const TypeInfo& type) {
    return type == error_type;
}

void ErrorValue::setStack(CallDumpList &callStack) {
    m_stack = callStack;
}

String &ErrorValue::toText() {
    return m_value;
}

CallDumpList &ErrorValue::stack() {
    return m_stack;
}
