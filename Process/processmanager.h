#ifndef PROCESSINGMANAGER_H
#define PROCESSINGMANAGER_H

#include "stepmanager.h"
#include "Calcul/memorymanager.h"
#include "Calcul/DataType/SystemInterface/iscsi.h"
#include "Util/stack.h"

class ProcessManager {
public:
    ProcessManager();

    void setSourceFile(const String &file);
    void setDefaultOutput(const String &output);

    void exec();
    ISCObject* call(Module *module, pos_t pos, ISCObject* self, const ISCObjectList& args);

    int checkExec();

private:
    StepManager m_stepManager;
    MemoryManager m_memory;

    ISCSIPtr m_defaultOutput;
    Stack<ISCSIPtr> m_output;

    ISCObject* m_return;
    ISCObject* m_throw;

private:
    StepFunction stepBalise;
    StepFunction stepBreak;
    StepFunction stepCalc;
    StepFunction stepCase;
    StepFunction stepCatch;
    StepFunction stepClass;
    StepFunction stepContinue;
    StepFunction stepDefault;
    StepFunction stepElse;
    StepFunction stepEnd;
    StepFunction stepEnum;
    StepFunction stepFor;
    StepFunction stepIf;
    StepFunction stepLoad;
    StepFunction stepPrint;
    StepFunction stepReturn;
    StepFunction stepSwitch;
    StepFunction stepThrow;
    StepFunction stepTry;
    StepFunction stepYield;
    StepFunction stepVisibility;
    StepFunction stepWhile;

    friend class Dictionary;

};

#endif // PROCESSINGMANAGER_H
