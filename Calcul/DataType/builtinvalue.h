#ifndef BUILTINVALUE_H
#define BUILTINVALUE_H

#include "Calcul/DataType/iscvalue.h"

class BuiltinValue : public ISCValue {
public:
    BuiltinValue();

    virtual ISCObject* get(ISCObject *requester, const String &member);
    virtual ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& args);
    void setFunctionMapping(ISCObjectMapping* mapping);

protected:
    ISCObjectMapping* m_fcts;
};

#endif // BUILTINVALUE_H
