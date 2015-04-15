#include "stringvalue.h"

StringValue::StringValue(ISCObjectMapping *fcts, String value) : BuiltinValue(fcts), m_value(value)
{}

bool StringValue::instanceOf(const TypeInfo& type) {
    return type == string_type;
}

ISCObject* StringValue::get(ISCObject* requester, const String& member) {
    return NULL;
}

ISCObject* StringValue::call(ISCObject* requester, const String& member, const ISCObjectList& args) {

}

String &StringValue::toString() {
    return m_value;
}
