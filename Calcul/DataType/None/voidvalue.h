#ifndef VOIDVALUE_H
#define VOIDVALUE_H

#include "Calcul/DataType/builtinvalue.h"

class VoidValue : public BuiltinValue {
public:
    VoidValue();

    bool inheritFrom(const TypeInfo &type);
    bool instanceOf(const TypeInfo& type);
    ISCObject* get(ISCObject* requester, const String& member);
};

typedef std::tr1::shared_ptr<VoidValue> VoidValuePtr;

#endif // VOIDVALUE_H
