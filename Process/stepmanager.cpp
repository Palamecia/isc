#include "stepmanager.h"

StepManager::StepManager(MemoryManager *memory)
    : m_memory(memory), m_skipMask(None)
{}

bool StepManager::execMode() {
    return !m_skipMask;
}

Step* StepManager::nextStep() {
    DataPointer& dp = m_callStack.top();
    return dp.module->step(dp.pos++, &m_dico);
}

void StepManager::call(const String& module, pos_t pos) {
    ModuleMapping::iterator it = m_moduleCache.find(module);
    if (it == m_moduleCache.end()) {
        m_moduleCache.insert(ModuleMapping::value_type(module, Module(module)));
    }
    m_callStack.push(DataPointer(&m_moduleCache[module], pos));

}

void StepManager::call(Module *module, pos_t pos) {
    m_callStack.push(DataPointer(module, pos));
}

void StepManager::exitCall() {
    m_callStack.pop();
}

StepManager::CtxPointer StepManager::lastClosedBlock() {
    return m_lastClosed;
}

void StepManager::startBlock(StructureType type) {
    m_ctxStack.push(CtxPointer(type, m_callStack.top().pos - 1));
    if (type != Call) m_memory->createSubContexte(); // Call contexte are create later
}

void StepManager::closeBlock() {
    m_lastClosed = m_ctxStack.pop();
    if (m_skipMask) m_lastClosed.executed = false;
    if (m_skipMask && m_ctxStack.size() <= m_skipLimit && m_skipMask & m_lastClosed.type) m_skipMask = None;
    if (m_lastClosed.type != Call) m_memory->closeContexte(); // Call contexte are delete later
}

void StepManager::skipBlock(unsigned int masque) {
    m_skipMask = masque;
    m_skipLimit = m_ctxStack.size();
}

void StepManager::restartBlock(unsigned int masque) {
    do {
        closeBlock();
    } while (!(m_lastClosed.type & masque));
    restartLastClosedBlock();
}

void StepManager::restartLastClosedBlock() {
    m_callStack.top().pos = m_lastClosed.pos;
}

void StepManager::dumpStack(List<CallDump>& dump) {
    Stack<DataPointer>::iterator it;
    for (it = m_callStack.begin(); it != m_callStack.end(); ++it) {
        CallDump line;
        line.module = it->module->name();
        line.line   = it->module->line(it->pos - 1);
        line.raw    = it->module->raw(it->pos - 1);
        dump.append(line);
    }
}
