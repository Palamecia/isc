#ifndef ISCOBJECT_H
#define ISCOBJECT_H

#include <tr1/memory>

#include "Util/list.h"
#include "Util/string.h"

#include "DataType/typeinfo.h"
#include "Syntax.h"

class ISCObject;
class ISCValue;

typedef List<ISCObject*> ISCObjectList;
typedef Map<String, ISCObject*> ISCObjectMapping;

class ISCObject {
public:
    enum AccesMask {
        ExternAcces     = 0x1,
        ChildAcces      = 0x2,
        StaticAcces     = 0x4,
        ConstRefAcces   = 0x8
    };
    typedef std::tr1::shared_ptr<ISCValue> ValuePtr;

    ISCObject(const TypeInfo& type = TypeDescriptor::BuiltIn[var_type], const String& name = String());
    ISCObject(const ISCObject& other, const String& name = String());

    void construct(ProcessManager* process, const ISCObjectList& params = ISCObjectList());

    bool instanceOf(const TypeInfo& type);
    bool inheritFrom(const TypeInfo& type);
    ISCObject* get(ISCObject* requester, const String& member);
    ISCObject* call(ISCObject* requester, const String& member, const ISCObjectList& params);

    String &name();
    ValuePtr value();

    bool operator < (const ISCObject& other) const;

    void init(ISCValue* value, byte accesMask = ExternAcces | ChildAcces);

#ifdef DEBUG
    static uint nb_instance;
#endif

private:
    String m_name;
    TypeInfo m_typeInfo;
    std::tr1::shared_ptr<ISCValue> m_value;
    byte m_accesMask;

    friend class ObjectDescriptor;
};

#endif // ISCOBJECT_H
