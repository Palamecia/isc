#include "typedescriptor.h"

TypeDescriptor::TypeDescriptor(const String &name)
    : MemberDescriptor(name)
{}

TypeDescriptor* TypeDescriptor::getType(const String& type) {
    return NULL;
}

bool TypeDescriptor::operator ==(TypeId id) const {
    return this == TypeDescriptor::BuiltIn[id];
}

bool TypeDescriptor::extend(const TypeDescriptor &other) const {
    return other == var_type;
}

Map<TypeId, TypeDescriptor*> TypeDescriptor::BuiltIn = Map<TypeId, TypeDescriptor*>();
