#include "iscvalue.h"

ISCValue::ISCValue()
{}

bool ISCValue::instanceOf(const TypeInfo& type) {
    return type == typeInfo();
}

bool ISCValue::inheritFrom(const TypeInfo& type) {
    return typeInfo().extend(type);
}
