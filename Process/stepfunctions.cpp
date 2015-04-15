#include "processmanager.h"
#include "Calcul/DataType/Boolean/booleanvalue.h"
#include "System/iscsourcemanager.h"
#include "System/errormanager.h"

#define exec_section if (m_stepManager.execMode())

void ProcessManager::stepBalise(Step* step) {
    if (step->isCreatingContext()) {
        m_stepManager.startBlock(StepManager::Markup);
    }

    exec_section {
        StringList& tokens = step->tokens();
        StringList buff;
        uint pos = 0;
        while (pos < tokens.size() && tokens[pos] != ":" && tokens[pos] != ">") {
            buff.append(tokens[pos++]);
        }

        ISCObject* object = m_memory.calc(buff);
        if (step->isCreatingContext()) m_memory.addStartElement(object);
        else m_memory.addEmptyElement(object);
        if (tokens[pos] == ">") return;

        buff.clear();
        while (tokens[pos] != ">") {
            if (pos >= tokens.size()) {
                // TODO : Erreur
            }
            buff.append(tokens[pos++]);
        }
        m_memory.createNewContexte(object);
        m_memory.calc(buff);
        m_memory.closeContexte();
    }
}

void ProcessManager::stepBreak(Step* step) {
    if (step->isCreatingContext()) {
        raise_error(UNEXPECTED_BLOC);
    }

    exec_section {
        m_stepManager.skipBlock(StepManager::Loop | StepManager::Case);
    }
}

void ProcessManager::stepCalc(Step* step) {
    if (step->isCreatingContext()) {
        m_stepManager.startBlock(StepManager::Definition);
    }

    exec_section {
        ISCObject* object = m_memory.calc(step->tokens());
        if (!m_output.isEmpty()) {
            m_output.top()->print(object);
        }
        delete object;
    }
}

void ProcessManager::stepCase(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Case);

    exec_section {
        if (!m_stepManager.lastClosedBlock().executed) {

        }
    }
}

void ProcessManager::stepCatch(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Catch);

    exec_section {
        if (m_stepManager.lastClosedBlock().type != StepManager::Try) {
            // TODO : Erreur
        }
        if (m_stepManager.lastClosedBlock().executed) {
            m_stepManager.skipBlock();
        }
    }
}

void ProcessManager::stepClass(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Typedef);
}

void ProcessManager::stepContinue(Step* step) {
    if (step->isCreatingContext()) {
        raise_error(UNEXPECTED_BLOC);
    }

    exec_section {
        m_stepManager.restartBlock(StepManager::Loop);
    }
}

void ProcessManager::stepDefault(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Case);
}

void ProcessManager::stepElse(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::EndCond);
    exec_section {
        if (m_stepManager.lastClosedBlock().type != StepManager::Condition) {
            // TODO : Erreur
        }
        if (m_stepManager.lastClosedBlock().executed) {
            m_stepManager.skipBlock();
        }
    }
}

void ProcessManager::stepEnd(Step* step) {
    m_stepManager.closeBlock();

    ISCObject * defautlReturn = NULL;
    switch (m_stepManager.lastClosedBlock().type) {
    case StepManager::Markup:
        exec_section {
            m_memory.closeElement();
        }
        break;
    case StepManager::Print:
        exec_section {
            m_output.pop();
        }
        break;
    case StepManager::Call:
        m_stepManager.exitCall();
        defautlReturn = new ISCObject(TypeDescriptor::BuiltIn[void_type]);
        defautlReturn->construct(this);
        m_return = defautlReturn;
        break;
    case StepManager::Loop:
        exec_section {
            if (m_stepManager.lastClosedBlock().executed)
                m_stepManager.restartLastClosedBlock();
        }
        break;
    case StepManager::Visibility:
        exec_section {
            m_memory.closeVisibility();
        }
    }
}

void ProcessManager::stepEnum(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Typedef);
}

void ProcessManager::stepFor(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Loop);
}

void ProcessManager::stepIf(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Condition);
}

void ProcessManager::stepLoad(Step* step) {
    exec_section {
        StringList modules = ISCSourceManager::instance()->moduleNames(step->tokens());
        for (uint i = 0; i < modules.size(); ++i) {
            m_stepManager.call(modules[i]);
            exec();
            m_stepManager.exitCall();
        }
    }
}

void ProcessManager::stepPrint(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Print);

    exec_section {
        if (step->tokens().isEmpty()) {
            m_output.push(m_defaultOutput);
        } else {
            // ...
        }
    }
}

void ProcessManager::stepReturn(Step* step) {
    if (step->isCreatingContext()) {
        raise_error(UNEXPECTED_BLOC);
    }
    exec_section {
        m_return = m_memory.calc(step->tokens());
    }
}

void ProcessManager::stepSwitch(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Switch);
}

void ProcessManager::stepTry(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Try);
}

void ProcessManager::stepThrow(Step* step) {
    if (step->isCreatingContext()) {
        raise_error(UNEXPECTED_BLOC);
    }

    exec_section {
        m_throw = m_memory.calc(step->tokens());
        m_stepManager.skipBlock(StepManager::Try);
    }
}

void ProcessManager::stepYield(Step* step) {
    if (step->isCreatingContext()) {
        raise_error(UNEXPECTED_BLOC);
    }
}

void ProcessManager::stepVisibility(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Visibility);
    exec_section {
        m_memory.setVisibility(step->tokens());
    }
}

void ProcessManager::stepWhile(Step* step) {
    if (!step->isCreatingContext()) {
        raise_error(EXPECTED_BLOC);
    }

    m_stepManager.startBlock(StepManager::Loop);
    exec_section {
        ISCObject* object = m_memory.calc(step->tokens());
        BooleanValuePtr value = std::tr1::dynamic_pointer_cast<BooleanValue>(object->value());
        delete object;
        if (!value) {
            // TODO : Erreur
        }
        if (!value->toBool()) m_stepManager.skipBlock(StepManager::Loop);
    }
}

