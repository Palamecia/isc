#ifndef STRINGVALUE_H
#define STRINGVALUE_H

#include "Calcul/DataType/builtinvalue.h"

class StringValue : public BuiltinValue {
public:
    StringValue(ISCObjectMapping *fcts, String value = String());

    virtual TypeInfo typeInfo();
    virtual ISCObject* get(ISCObject* requester, const String& member);
    virtual ISCObject* call(ISCObject* requester, const String& member, const ISCObjectList& args);

    String &toString();

private:
    String m_value;
};

typedef std::tr1::shared_ptr<StringValue> StringValuePtr;

#endif // STRINGVALUE_H
