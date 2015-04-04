#ifndef BOOLEANDESCRIPTOR_H
#define BOOLEANDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class BooleanValue;

class BooleanDescriptor : public TypeDescriptor {
public:
    BooleanDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static BooleanValue* makeValue(const String& raw);
};

#endif // BOOLEANDESCRIPTOR_H
