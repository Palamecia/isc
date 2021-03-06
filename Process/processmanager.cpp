#include "processmanager.h"

ProcessManager::ProcessManager()
    : m_stepManager(&m_memory),
    m_return(NULL),
    m_throw(NULL),
    m_loopBack(false) {
    m_memory.setProcess(this);
}

void ProcessManager::setSourceFile(const String &file) {
    m_stepManager.call(file);
}

void ProcessManager::setDefaultOutput(const String& output) {
    ISCObject* outputObject = m_memory.calc(StringList() << output);
    if (ISCSIPtr interface = std::tr1::dynamic_pointer_cast<ISCSI>(outputObject->value())) {
        m_defaultOutput = interface;
        delete outputObject;
    } else {
        delete outputObject;
        // TODO : Erreur
    }
}

void ProcessManager::exec() {
    Step* step;
    while ((!m_return) && (step = m_stepManager.nextStep())) {
        try {
            step->exec(this);
        } catch (ISCObject* err) {
            // dump call stack
            using namespace std::tr1;
            if (ErrorValuePtr value = dynamic_pointer_cast<ErrorValue>(err->value())) {
                CallDumpList stackDump;
                m_stepManager.dumpStack(stackDump);
                value->setStack(stackDump);
            }
            m_throw = err;
            m_stepManager.skipBlock(StepManager::Try);
            if (m_stepManager.readingFromInterface()) break;
        }
    }
}

ISCObject *ProcessManager::call(Module* module, pos_t pos, ISCObject *self, const ISCObjectList& args) {
    m_stepManager.call(module, pos);
    m_memory.createNewContexte(self);
    Step* header = m_stepManager.nextStep();
    m_memory.initContexte(header->tokens(), args);
    exec();
    m_memory.closeContexte();
    return m_return;
}

int ProcessManager::checkExec() {
    if (m_throw) {
        m_defaultOutput->catchError(m_throw);
        return -1;
    }
    return 0;
}
