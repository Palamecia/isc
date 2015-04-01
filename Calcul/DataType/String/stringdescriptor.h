#ifndef STRINGDESCRIPTOR_H
#define STRINGDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class StringValue;

class StringDescriptor : public TypeDescriptor {
public:
    StringDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);
    static StringValue* makeValue(const String& raw);
};

#endif // STRINGDESCRIPTOR_H
