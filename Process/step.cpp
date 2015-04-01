#include "step.h"
#include "dictionary.h"
#include "processmanager.h"

Step::Step(uint line, StepFunctionPtr fct)
    : m_line(line),
    m_fct(fct),
    m_subCtx(false)
{}

void Step::addToken(const String& token) {
    m_tokens.append(token);
}

void Step::createContexte() {
    m_subCtx = true;
}

void Step::exec(ProcessManager *process) {
    (process->*m_fct)(this);
}

bool Step::isCreatingContext() {
    return m_subCtx;
}

StringList& Step::tokens() {
    return m_tokens;
}
