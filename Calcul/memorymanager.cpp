#include "memorymanager.h"
#include "DataType/Error/errordescriptor.h"
#include "DataType/Integer/integervalue.h"
#include "DataType/Boolean/booleanvalue.h"
#include "DataType/String/stringvalue.h"
#include "DataType/SystemInterface/iscsidescriptror.h"
#include "System/iscsourcemanager.h"
#include "Syntax.h"

MemoryManager::MemoryManager()
    : m_process(NULL),
      m_application("Application") {
    m_application.declareType(TypeDescriptor::BuiltIn[var_type] ? TypeDescriptor::BuiltIn[var_type] : new VarDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[void_type] ? TypeDescriptor::BuiltIn[void_type] : new VoidDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[error_type] ? TypeDescriptor::BuiltIn[error_type] : new ErrorDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[int_type] ? TypeDescriptor::BuiltIn[int_type] : new IntegerDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[float_type] ? TypeDescriptor::BuiltIn[float_type] : new FloatDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[bool_type] ? TypeDescriptor::BuiltIn[bool_type] : new BooleanDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[string_type] ? TypeDescriptor::BuiltIn[string_type] : new StringDescriptor);
    m_application.declareType(TypeDescriptor::BuiltIn[color_type] ? TypeDescriptor::BuiltIn[color_type] : new ColorDescriptor);
    loadSystemInterfaces();
}

void MemoryManager::loadSystemInterfaces() {
    StringList interfaces = ISCSourceManager::instance()->listInterfaces();
    for (uint i = 0; i < interfaces.size(); ++i) {
        m_application.declareType(new ISCSIDescriptror(interfaces[i]));
    }
}

void MemoryManager::setProcess(ProcessManager* process) {
    m_process = process;
    ISCObject * root = new ISCObject(TypeInfo(&m_application), this_key_word);
    root->construct(m_process);
    m_stack.createContexte(root);
}

void MemoryManager::setVisibility(const StringList& tockens) {
    byte visibility = 0;
    for (int i = 0; i < tockens.size(); ++i) {
        if (tockens[i] == public_tocken) {
            visibility |= ISCObject::ExternAcces;
            visibility |= ISCObject::ChildAcces;
        }
        else if (tockens[i] == protected_tocken) {
            visibility &= ~ISCObject::ExternAcces;
            visibility |= ISCObject::ChildAcces;
        }
        else if (tockens[i] == private_tocken) {
            visibility &= ~ISCObject::ExternAcces;
            visibility &= ~ISCObject::ChildAcces;
        }
        else if (tockens[i] == static_tocken) {
            visibility &= ~ISCObject::StaticAcces;
        }
        else {
            // TODO : Erreur
        }
    }
    m_visibility.push(visibility);
}

void MemoryManager::closeVisibility() {
    m_visibility.pop();
}

ISCObject* MemoryManager::calc(Calcul calcul) {
    if (ISCObject* object = calcul.build(this)) {
        if (!m_stack.push(object)) {
            // TODO : Erreur
        }
    }
    m_stack.createSubContexte(); // calc contexte
    ISCObjectList results = calcul.resolve(this);
    m_stack.closeSubContexte();

    switch (results.size()) {
    case 0: return new ISCObject(TypeDescriptor::BuiltIn[void_type]);
    case 1: return results.first();
    }
    // create and return value
}

void MemoryManager::createNewContexte(ISCObject* self) {
    m_stack.createContexte(self);
}

void MemoryManager::createSubContexte() {
    m_stack.createSubContexte();
}

void MemoryManager::closeContexte() {
    m_stack.closeSubContexte();
}

void MemoryManager::initContexte(const StringList& tokens, const ISCObjectList& args) {

}

void MemoryManager::addEmptyElement(const ISCObject *element) {

}

void MemoryManager::addStartElement(const ISCObject *element) {

}

void MemoryManager::closeElement() {

}

ISCObject* MemoryManager::getObject(const String& tocken) {
    if (ISCObject* object = m_stack.get(tocken)) return object;
    if (ISCValue* value = IntegerDescriptor::makeValue(tocken)) {
        ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[int_type]);
        object->construct(m_process);
        object->init(value);
        m_stack.push(object);
        return object;
    }
    if (ISCValue* value = StringDescriptor::makeValue(tocken)) {
        ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[string_type]);
        object->construct(m_process);
        object->init(value);
        m_stack.push(object);
        return object;
    }
    if (ISCValue* value = BooleanDescriptor::makeValue(tocken)) {
        ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[bool_type]);
        object->construct(m_process);
        object->init(value);
        m_stack.push(object);
        return object;
    }
    if (tocken == null_key_word) {
        ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[void_type]);
        m_stack.push(object);
        return object;
    }
    // gestion constantes
    return NULL;
}

TypeDescriptor* MemoryManager::getType(const String& tocken, TypeDescriptor* parent) {
    if (!parent) parent = &m_application;
    return parent->getType(tocken);
}
