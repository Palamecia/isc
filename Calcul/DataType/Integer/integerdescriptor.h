#ifndef INTEGERDESCRIPTOR_H
#define INTEGERDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/iscobject.h"
#include "Syntax.h"

class IntegerValue;

class IntegerDescriptor : public TypeDescriptor {
public:
    IntegerDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);
    static IntegerValue* makeValue(const String& raw);

private:
    static ISCObjectMapping* m_fcts;
};

#endif // INTEGERDESCRIPTOR_H
