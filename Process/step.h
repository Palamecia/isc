#ifndef STEP_H
#define STEP_H

#include "Util/string.h"

class ProcessManager;

class Step;
typedef void (StepFunction)(Step* step);
typedef void (ProcessManager::* StepFunctionPtr)(Step* step);

class Step {
public:
    void exec(ProcessManager* process);
    bool isCreatingContext();

    StringList& tokens();
    inline String lastToken() { return m_tokens.last(); }

    inline uint line() { return m_line; }
private:
    Step(uint line, StepFunctionPtr fct);

    void addToken(const String &token);
    void createContexte();

    uint            m_line;
    StepFunctionPtr m_fct;
    StringList      m_tokens;
    bool            m_subCtx;

    friend class ISCParser;
    friend class Dictionary;
};

#endif // STEP_H
