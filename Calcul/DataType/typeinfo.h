#ifndef TYPEINFO_H
#define TYPEINFO_H

#include "Util/list.h"
#include "Util/string.h"
#include "typedescriptor.h"

class TypeInfo {
public:
    enum Modifier {
        list,
        hash,
        const_ref
    };
    typedef List<Modifier> ModifierList;

    TypeInfo(const TypeInfo& other);
    TypeInfo(const TypeId id);
    TypeInfo(TypeDescriptor* descriptor);
    TypeInfo(TypeDescriptor* descriptor, ModifierList modifiers);

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte& accesMask, ISCObject* instance);

    String typeName() const;
    const TypeDescriptor* descriptor() const;
    const ModifierList& modifiers() const;
    ModifierList& modifiers();

    bool operator ==(const TypeInfo& other) const;
    bool operator ==(TypeId id) const;

private:
    TypeDescriptor* m_descriptor;
    ModifierList m_modifiers;
};

#endif // TYPEINFO_H
