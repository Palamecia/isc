#ifndef USERFUNCTION_H
#define USERFUNCTION_H

#include "functionvalue.h"
#include "Util/typedefs.h"
#include "Process/stepmanager.h"

class ProcessManager;

class UserFunction : public FunctionValue {
public:
    struct Shape {
        byte pc;
        TypeInfo * pt;
        Module * module;
        pos_t pos;
    };

    UserFunction(ProcessManager* process);
    ~UserFunction();

    ISCObject* run(ISCObject *self, const ISCObjectList& params);

private:
    ProcessManager* m_process;
    List<Shape> m_shapes;
};

#endif // USERFUNCTION_H
