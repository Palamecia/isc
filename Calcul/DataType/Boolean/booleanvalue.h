#ifndef BOOLEANVALUE_H
#define BOOLEANVALUE_H

#include "Calcul/DataType/builtinvalue.h"
#include "Syntax.h"

class BooleanValue : public BuiltinValue {
public:
    BooleanValue(ISCObjectMapping *fcts, bool value = false);

    virtual TypeInfo typeInfo();
    virtual ISCObject* get(ISCObject* requester, const String& member);
    virtual ISCObject* call(ISCObject* requester, const String& member, const ISCObjectList& args);

    bool &toBool();

private:
    bool m_value;
};

typedef std::tr1::shared_ptr<BooleanValue> BooleanValuePtr;

#endif // BOOLEANVALUE_H
