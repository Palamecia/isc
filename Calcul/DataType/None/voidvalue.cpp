#include "voidvalue.h"
#include "System/errormanager.h"

VoidValue::VoidValue() : BuiltinValue(NULL)
{}

TypeInfo VoidValue::typeInfo() {
    return void_type;
}

ISCObject* VoidValue::get(ISCObject*, const String& member) {
    raise_error(UNKNOWN_MEMBER, void_key_word, member.c_str());
    return NULL;
}

ISCObject* VoidValue::call(ISCObject*, ISCObject*, const String& member, const ISCObjectList&) {
    raise_error(UNKNOWN_METHODE, void_key_word, member.c_str());
    return NULL;
}
