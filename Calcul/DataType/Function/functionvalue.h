#ifndef FUNCTIONVALUE_H
#define FUNCTIONVALUE_H

#include "Calcul/DataType/iscvalue.h"

class FunctionValue : public ISCValue {
public:
    FunctionValue();

    bool instanceOf(const TypeInfo& type);
    bool inheritFrom(const TypeInfo& type);
    ISCObject* get(ISCObject* requester, const String& member);
    ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& params);
    virtual ISCObject* run(ISCObject *self, const ISCObjectList& params)=0;
};

typedef std::tr1::shared_ptr<FunctionValue> FunctionValuePtr;

#endif // FUNCTIONVALUE_H
