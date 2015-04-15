#ifndef ERRORDESCRIPTOR_H
#define ERRORDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/iscobject.h"
#include "Syntax.h"

class ErrorValue;

class ErrorDescriptor : public TypeDescriptor {
public:
    ErrorDescriptor();

    void createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance);
    static ErrorValue* makeValue(const String& raw);
    static ErrorValue* fromData(const String &data);

private:
    static ISCObjectMapping* m_fcts;
};

#endif // ERRORDESCRIPTOR_H
