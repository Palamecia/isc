#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include "iscobject.h"
#include "contextestack.h"
#include "Util/string.h"
#include "DataType/Class/classdescriptor.h"

#include "DataType/Variant/vardescriptor.h"
#include "DataType/None/voiddescriptor.h"
#include "DataType/Integer/integerdescriptor.h"
#include "DataType/Float/floatdescriptor.h"
#include "DataType/Boolean/booleandescriptor.h"
#include "DataType/String/stringdescriptor.h"
#include "DataType/Color/colordescriptor.h"

#include "Syntax.h"

class ProcessManager;

class MemoryManager {
public:
    MemoryManager();
    void setProcess(ProcessManager* process);

    void setVisibility(const StringList& tockens);
    void closeVisibility();

    ISCObject *calc(Calcul calcul);

    void createNewContexte(ISCObject *self);
    void createSubContexte();
    void closeContexte();
    void initContexte(const StringList& tokens, const ISCObjectList& args);

    void addEmptyElement(const ISCObject *element);
    void addStartElement(const ISCObject *element);
    void closeElement();

    ISCObject* getObject(const String& tocken);
    TypeDescriptor* getType(const String& tocken, TypeDescriptor* parent = NULL);

private:
    void loadSystemInterfaces();

private:
    ProcessManager* m_process;
    ClassDescriptor m_application;

    Stack<byte> m_visibility;

    ContexteStack m_stack;

    friend class Calcul;
};

#endif // MEMORYMANAGER_H
