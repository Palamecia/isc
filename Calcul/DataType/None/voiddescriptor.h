#ifndef VOIDDESCRIPTOR_H
#define VOIDDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/DataType/iscvalue.h"
#include "Syntax.h"

class VoidDescriptor : public TypeDescriptor {
public:
    VoidDescriptor();

    bool extend(const TypeDescriptor &other) const;
    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static ISCObject* instance();

private:
    static ISCValuePtr m_none;
    static ISCObject* m_instance;
};

#endif // VOIDDESCRIPTOR_H
