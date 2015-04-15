#include "Calcul/DataType/SystemInterface/iscsi.h"

#ifndef STDIO_H
#define STDIO_H

class stdio : public ISCSI {
public:
    stdio();
    ~stdio();

    virtual String nextInstruction();
    virtual void execPrint(ISCObject* object);
    virtual void catchError(ISCObject *error);
};

isc_share(stdio)

#endif // STDIO_H
