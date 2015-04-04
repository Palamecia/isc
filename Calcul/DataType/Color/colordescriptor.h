#ifndef COLORDESCRIPTOR_H
#define COLORDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Syntax.h"

class ColorDescriptor : public TypeDescriptor {
public:
    ColorDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
};

#endif // COLORDESCRIPTOR_H
