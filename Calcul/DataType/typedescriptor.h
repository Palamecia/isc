#ifndef TYPEDESCRIPTOR_H
#define TYPEDESCRIPTOR_H

#include "memberdescriptor.h"
#include "Util/map.h"

enum TypeId {
    var_type,
    void_type,
    error_type,
    int_type,
    float_type,
    bool_type,
    string_type,
    color_type
};

class TypeDescriptor : public MemberDescriptor {
public:
    TypeDescriptor(const String& name);

    virtual TypeDescriptor* getType(const String& type);

    bool operator ==(TypeId id) const;

    virtual bool extend(const TypeDescriptor &other) const;

    static Map<TypeId, TypeDescriptor*> BuiltIn;
};

#endif // TYPEDESCRIPTOR_H
