#ifndef VARDESCRIPTOR_H
#define VARDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class VarDescriptor : public TypeDescriptor {
public:
    VarDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);
};

#endif // VARDESCRIPTOR_H
