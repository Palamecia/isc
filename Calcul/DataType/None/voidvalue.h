#ifndef VOIDVALUE_H
#define VOIDVALUE_H

#include "Calcul/DataType/builtinvalue.h"

class VoidValue : public BuiltinValue {
public:
    VoidValue();

    virtual TypeInfo typeInfo();
    ISCObject* get(ISCObject* requester, const String& member);
    ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& args);
};

typedef std::tr1::shared_ptr<VoidValue> VoidValuePtr;

#endif // VOIDVALUE_H
