#ifndef ISCVALUE_H
#define ISCVALUE_H

#include "Util/string.h"
#include "Util/list.h"

#include "Calcul/iscobject.h"

class ISCValue {
public:
    ISCValue();

    virtual bool inheritFrom(const TypeInfo& type);
    virtual bool instanceOf(const TypeInfo& type) = 0;
    virtual ISCObject *get(ISCObject *requester, const String& member) = 0;
    virtual ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& args) = 0;
};

#endif // ISCVALUE_H
