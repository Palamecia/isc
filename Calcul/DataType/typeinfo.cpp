#include "typeinfo.h"
#include "Calcul/iscobject.h"

TypeInfo::TypeInfo(const TypeInfo& other)
    : m_descriptor(other.m_descriptor),
      m_modifiers(other.m_modifiers)
{}

TypeInfo::TypeInfo(const TypeId id)
    : m_descriptor(TypeDescriptor::BuiltIn[id])
{}

TypeInfo::TypeInfo(TypeDescriptor *descriptor)
    : m_descriptor(descriptor)
{}

TypeInfo::TypeInfo(TypeDescriptor *descriptor, ModifierList modifiers)
    : m_descriptor(descriptor),
      m_modifiers(modifiers)
{}

void TypeInfo::createInstance(ProcessManager* process, const List<ISCObject*>& params, byte& accesMask, ISCObject* instance) {
    if (m_modifiers.isEmpty()) {
        m_descriptor->createInstance(process, params, accesMask, instance);
    } else {
        ModifierList subModifier = modifiers();
        while (subModifier.last() == const_ref) {
            accesMask |= ISCObject::ConstRefAcces;
            subModifier.pop_back();
        }
        int pos = 0;
        while (pos < subModifier.size() && subModifier[pos] == const_ref) ++pos;
        switch (subModifier[pos]) {
        case list:
            subModifier.removeAt(pos);
            // ...
            break;
        case hash:
            subModifier.removeAt(pos);
            // ...
            break;
        default: break;
        }

    }
}

String TypeInfo::typeName() const {
    return m_descriptor->name();
}

const TypeDescriptor* TypeInfo::descriptor() const {
    return m_descriptor;
}

const TypeInfo::ModifierList& TypeInfo::modifiers() const {
    return m_modifiers;
}

TypeInfo::ModifierList& TypeInfo::modifiers() {
    return m_modifiers;
}

bool TypeInfo::operator ==(const TypeInfo& other) const {
    return descriptor() == other.descriptor() && modifiers() == other.modifiers();
}

bool TypeInfo::operator ==(TypeId id) const {
    return descriptor() == TypeDescriptor::BuiltIn[id];
}
