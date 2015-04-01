#ifndef STEPMANAGER_H
#define STEPMANAGER_H

#include "module.h"
#include "Util/stack.h"
#include "Calcul/memorymanager.h"

struct CallDump {
    String  module;
    uint    line;
    String  raw;
};

class StepManager {
public:
    StepManager(MemoryManager* memory);

    enum StructureType {
        None        = 0x00000000,
        Markup      = 0x00000001,
        Definition  = 0x00000002,
        Typedef     = 0x00000004,
        Visibility  = 0x00000008,
        Try         = 0x00000010,
        Catch       = 0x00000020,
        Print       = 0x00000040,
        Switch      = 0x00000080,
        Case        = 0x00000100,
        Loop        = 0x00000200,
        Condition   = 0x00000400,
        EndCond     = 0x00000800,
        Call        = 0x00001000,
        Any         = 0xFFFFFFFF
    };

    class DataPointer {
    public:
        DataPointer() : module(NULL), pos(0) {}
        DataPointer(Module *m) : module(m), pos(0) {}
        DataPointer(Module *m, pos_t& p) : module(m), pos(p) {}
        Module* module;
        pos_t pos;
    };

    class CtxPointer {
    public:
        CtxPointer() : type(None), pos(0), executed(true) {}
        CtxPointer(StructureType t, pos_t p) : type(t), pos(p), executed(true) {}
        StructureType type;
        pos_t pos;
        bool executed;
    };

    bool execMode();

    Step* nextStep();
    void call(const String &module, pos_t pos = 0);
    void call(Module *module, pos_t pos = 0);
    void exitCall();

    CtxPointer lastClosedBlock();
    void startBlock(StructureType type);
    void closeBlock();
    void skipBlock(unsigned int masque = Any);
    void restartBlock(unsigned int masque = Any);
    void restartLastClosedBlock();

    void dumpStack(List<CallDump>& dump);
private:
    typedef Map<String, Module> ModuleMapping;
    ModuleMapping       m_moduleCache;
    Stack<DataPointer>  m_callStack;
    Stack<CtxPointer>   m_ctxStack;
    CtxPointer          m_lastClosed;
    MemoryManager*      m_memory;

    unsigned int        m_skipMask;
    int                 m_skipLimit;

    Dictionary m_dico;
};

#endif // STEPMANAGER_H
