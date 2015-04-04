#ifndef FLOATDESCRIPTOR_H
#define FLOATDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class FloatDescriptor : public TypeDescriptor {
public:
    FloatDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
};

#endif // FLOATDESCRIPTOR_H
