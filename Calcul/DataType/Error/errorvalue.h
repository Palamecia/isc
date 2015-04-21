#ifndef ERRORVALUE_H
#define ERRORVALUE_H

#include "Calcul/DataType/builtinvalue.h"

struct CallDump {
    String  module;
    uint    line;
    String  raw;
};
typedef List<CallDump> CallDumpList;

class ErrorValue : public BuiltinValue {
public:
    ErrorValue(ISCObjectMapping *fcts, const String& value = "Runtime error");

    virtual TypeInfo typeInfo();

    void setStack(CallDumpList &callStack);

    String &toText();
    CallDumpList &stack();

private:
    String m_value;
    CallDumpList m_stack;
};

typedef std::tr1::shared_ptr<ErrorValue> ErrorValuePtr;

#endif // ERRORVALUE_H
