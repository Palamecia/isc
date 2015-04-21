#ifndef INTEGERVALUE_H
#define INTEGERVALUE_H

#include "Calcul/DataType/builtinvalue.h"

class IntegerValue : public BuiltinValue {
public:
    IntegerValue(ISCObjectMapping *fcts, const int value = 0);

    virtual TypeInfo typeInfo();

    int &toInt();

private:
    int m_value;
};

typedef std::tr1::shared_ptr<IntegerValue> IntegerValuePtr;

#endif // INTEGERVALUE_H
