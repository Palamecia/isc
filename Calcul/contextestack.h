#ifndef CONTEXTESTACK_H
#define CONTEXTESTACK_H

#include "Util/stack.h"
#include "contexte.h"

class ContexteStack {
public:
    ContexteStack();

    void createContexte(ISCObject *thisObject);
    void createSubContexte();
    void closeSubContexte();
    void closeContexte();

    inline ISCObject* get(const String& object) { return m_stack.top()->get(object); }
    inline ISCObject* get(const String& object, const String& member) { return m_stack.top()->get(object, member); }
    inline ISCObject* call(const String& member, const ISCObjectList& params) { return m_stack.top()->call(member, params); }
    inline ISCObject *call(const String& object, const String& member, const ISCObjectList& params) { return m_stack.top()->call(object, member, params); }
    bool push(ISCObject* object);
private:
    Stack<Contexte*> m_stack;
};

#endif // CONTEXTESTACK_H
