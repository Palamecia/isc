#include "stringvalue.h"

StringValue::StringValue(String value) : m_value(value)
{}

bool StringValue::instanceOf(const TypeInfo& type) {
    return type == string_type;
}

ISCObject* StringValue::get(ISCObject* requester, const String& member) {
    return NULL;
}

ISCObject* StringValue::call(ISCObject* requester, const String& member, const ISCObjectList& params) {

}

String &StringValue::toString() {
    return m_value;
}
