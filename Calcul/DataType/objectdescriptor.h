#ifndef OBJECTDESCRIPTOR_H
#define OBJECTDESCRIPTOR_H

#include "memberdescriptor.h"
#include "Calcul/iscobject.h"

class ObjectDescriptor : public MemberDescriptor {
public:
    ObjectDescriptor(byte accesMask, const TypeInfo &type, const String& name);

    ISCObject *newObject();
    void createInstance(ProcessManager* process, const ISCObjectList& args, byte accesMask, ISCObject* instance);

    byte accesMask();

private:
    byte m_accesMask;
    TypeInfo m_typeInfo;
};

#endif // OBJECTDESCRIPTOR_H
