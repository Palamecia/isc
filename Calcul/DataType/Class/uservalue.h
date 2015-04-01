#ifndef USERVALUE_H
#define USERVALUE_H

#include "Calcul/DataType/iscvalue.h"
#include "classdescriptor.h"

class UserValue : public ISCValue {
public:
    UserValue(ClassDescriptor* typeId);

    virtual bool instanceOf(const TypeInfo& type);
    virtual bool inheritFrom(const TypeInfo& type);
    virtual ISCObject* get(ISCObject* requester, const String& member);
    virtual ISCObject* call(ISCObject* requester, ISCObject* self, const String& member, const ISCObjectList& params);

private:
    friend class ClassDescriptor;
    void addParent();
    void addMember(ISCObject *object);

private:
    ClassDescriptor* m_typeId;
    ISCObjectMapping m_members;
    ISCObjectMapping m_vtable;
};

#endif // USERVALUE_H
