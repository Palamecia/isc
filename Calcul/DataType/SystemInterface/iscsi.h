#ifndef ISCSI_H
#define ISCSI_H

#include "Calcul/DataType/builtinvalue.h"

class ISCSIDescriptror;

class ISCSI : public BuiltinValue {
public:
    ISCSI();
    void print(ISCObject* object);
    virtual String nextInstruction();
    virtual void catchError(ISCObject *error);

    virtual bool instanceOf(const TypeInfo& type);
    virtual ISCObject* get(ISCObject* requester, const String& member);

protected:
    void setPrintEnabeled(const bool enable);

    virtual void execPrint(ISCObject* object);

private:
    bool m_printEnabeled;
};

typedef std::tr1::shared_ptr<ISCSI> ISCSIPtr;

typedef ISCSI* (*ISCSIBuilder)();

#define isc_share(iscsi_name) \
    extern "C" { \
        ISCSI* iscsi_new() { \
            return new iscsi_name(); \
        } \
    }

#endif // ISCSI_H
