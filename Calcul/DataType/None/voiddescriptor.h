#ifndef VOIDDESCRIPTOR_H
#define VOIDDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class VoidDescriptor : public TypeDescriptor {
public:
    VoidDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);

private:
    static ISCObject* m_noneObject;
};

#endif // VOIDDESCRIPTOR_H
