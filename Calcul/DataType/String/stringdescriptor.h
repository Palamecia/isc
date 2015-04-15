#ifndef STRINGDESCRIPTOR_H
#define STRINGDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/iscobject.h"
#include "Syntax.h"

class StringValue;

class StringDescriptor : public TypeDescriptor {
public:
    StringDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static StringValue* makeValue(const String& raw);

private:
    static ISCObjectMapping* m_fcts;
};

#endif // STRINGDESCRIPTOR_H
