#include "typedescriptor.h"

TypeDescriptor::TypeDescriptor(const String &name)
    : MemberDescriptor(name)
{}

TypeDescriptor* TypeDescriptor::getType(const String& type) {
    return NULL;
}

Map<TypeId, TypeDescriptor*> TypeDescriptor::BuiltIn = Map<TypeId, TypeDescriptor*>();
