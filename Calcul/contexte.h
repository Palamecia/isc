#ifndef CONTEXTE_H
#define CONTEXTE_H

#include "iscobject.h"
#include "calcul.h"
#include "Util/map.h"
#include "Syntax.h"

class ProcessManager;

class Contexte {
public:
    Contexte(ISCObject* ctx_self);
    Contexte(Contexte *parent = NULL);

    ISCObject* get(const String& object);
    ISCObject* get(const String& object, const String& member);
    ISCObject* call(const String& member, const ISCObjectList& args);
    ISCObject *call(const String& object, const String& member, const ISCObjectList& args);

    bool contains(ISCObject* obj);
    bool insert(ISCObject* obj);

    Contexte* parent();

    Contexte *clear();

private:
    Contexte* m_parent;
    ISCObjectMapping m_objects;
};

#endif // CONTEXTE_H
