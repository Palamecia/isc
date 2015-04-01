#ifndef ISCSIDESCRIPTROR_H
#define ISCSIDESCRIPTROR_H

#include "Calcul/DataType/typedescriptor.h"
#include "iscsi.h"

class ISCSIDescriptror : public TypeDescriptor {
public:
    ISCSIDescriptror(const String& name);

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);
};

#endif // ISCSIDESCRIPTROR_H
