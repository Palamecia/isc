#ifndef CLASSDESCRIPTOR_H
#define CLASSDESCRIPTOR_H

#include "Calcul/DataType/typedescriptor.h"
#include "Calcul/DataType/objectdescriptor.h"
#include "Calcul/contexte.h"
#include "Util/map.h"
#include "Syntax.h"

class ClassDescriptor : public TypeDescriptor {
public:
    ClassDescriptor(const String& name);
    ~ClassDescriptor();

    TypeDescriptor* getType(const String& type);

    void createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance);

    void declareParent(TypeDescriptor * parent);
    void declareType(TypeDescriptor * type);
    void declareMember(ObjectDescriptor * object);

private:
    typedef Map<String, MemberDescriptor*> MemberMap;

    Contexte m_staticContexte;
    MemberMap m_members;
};

#endif // CLASSDESCRIPTOR_H
