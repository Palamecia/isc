#include "iscvalue.h"

ISCValue::ISCValue()
{}

bool ISCValue::inheritFrom(const TypeInfo& type) {
    return type == var_type;
}
