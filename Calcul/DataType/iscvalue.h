#ifndef ISCVALUE_H
#define ISCVALUE_H

#include "Util/string.h"
#include "Util/list.h"

#include "Calcul/iscobject.h"

class ISCValue {
public:
    ISCValue();

    virtual TypeInfo typeInfo() = 0;
    bool instanceOf(const TypeInfo& type);
    bool inheritFrom(const TypeInfo& type);

    virtual ISCObject *get(ISCObject *requester, const String& member) = 0;
    virtual ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& args) = 0;
};

typedef std::tr1::shared_ptr<ISCValue> ISCValuePtr;

#endif // ISCVALUE_H
