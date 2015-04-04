#ifndef MEMBERDESCRIPTOR_H
#define MEMBERDESCRIPTOR_H

#include "Util/typedefs.h"
#include "Util/string.h"
#include "Util/list.h"

class ISCObject;
class ProcessManager;

class MemberDescriptor {
public:
    MemberDescriptor(const String& name);
    virtual void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) = 0;

    String name();

protected:
    String m_name;
};

#endif // MEMBERDESCRIPTOR_H
