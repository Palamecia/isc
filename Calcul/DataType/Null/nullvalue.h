#ifndef NULLVALUE_H
#define NULLVALUE_H

#include "Calcul/DataType/builtinvalue.h"

class NullValue : public BuiltinValue {
public:
    NullValue();

    virtual TypeInfo typeInfo();
    ISCObject* get(ISCObject* requester, const String& member);
    ISCObject* call(ISCObject *requester, ISCObject *self, const String &member, const ISCObjectList &args);
};

typedef std::tr1::shared_ptr<NullValue> NullValuePtr;

#endif // NULLVALUE_H
