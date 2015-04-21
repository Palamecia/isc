#ifndef NULLDESCRIPTOR_H
#define NULLDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/DataType/iscvalue.h"
#include "Syntax.h"

class NullDescriptor : public TypeDescriptor {
public:
    NullDescriptor();

    bool extend(const TypeDescriptor &other) const;
    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static ISCObject* instance();

private:
    static ISCValuePtr m_null;
    static ISCObject* m_instance;
    static NullDescriptor* m_singleton;
};

#endif // NULLDESCRIPTOR_H
