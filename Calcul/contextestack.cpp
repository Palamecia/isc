#include "contextestack.h"

ContexteStack::ContexteStack()
{}

void ContexteStack::createContexte(ISCObject* ctx_self) {
    m_stack.push(new Contexte(ctx_self));
}

void ContexteStack::createSubContexte() {
    m_stack.push(new Contexte(m_stack.top()));
}

void ContexteStack::closeSubContexte() {
    delete m_stack.pop()->clear();
}

void ContexteStack::closeContexte() {
    bool good = true;
    while (good) {
        good = m_stack.top()->parent() != NULL;
        delete m_stack.pop()->clear();
    }
}

bool ContexteStack::push(ISCObject* object) {
    return m_stack.top()->insert(object);
}
