#ifndef BOOLEANDESCRIPTOR_H
#define BOOLEANDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/iscobject.h"
#include "Syntax.h"

class BooleanValue;

class BooleanDescriptor : public TypeDescriptor {
public:
    BooleanDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static BooleanValue* makeValue(const String& raw);
    static BooleanValue* fromData(bool data);

private:
    static ISCObjectMapping* m_fcts;
};

#endif // BOOLEANDESCRIPTOR_H
