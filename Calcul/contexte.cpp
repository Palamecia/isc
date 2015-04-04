#include "contexte.h"
#include "Process/processmanager.h"

Contexte::Contexte(ISCObject *ctx_self) : m_parent(NULL) {
    insert(new ISCObject(*ctx_self, this_key_word));
}

Contexte::Contexte(Contexte *parent) : m_parent(parent)
{}

ISCObject* Contexte::get(const String& object) {
     ISCObjectMapping::iterator it = m_objects.find(object);
     if (it != m_objects.end()) return it->second;
     if (m_parent) return m_parent->get(object);
     if (ISCObject* found = get(this_key_word, object)) return found;
     return NULL;
}

ISCObject *Contexte::get(const String& object, const String& member) {
    return get(object)->get(get(this_key_word), member);
}

ISCObject *Contexte::call(const String& member, const ISCObjectList& args) {
    return get(this_key_word)->call(get(this_key_word), member, args);
}

ISCObject* Contexte::call(const String& object, const String& member, const ISCObjectList& args) {
    return get(object)->call(get(this_key_word), member, args);
}

bool Contexte::contains(ISCObject* obj) {
    if (m_objects.find(obj->name()) != m_objects.end()) {
        return true;
    }
    if (m_parent) {
        return m_parent->contains(obj);
    }
    return false;
}

bool Contexte::insert(ISCObject *obj) {
    if (contains(obj)) return false;
    m_objects.insert(ISCObjectMapping::value_type(obj->name(), obj));
    return true;
}

Contexte* Contexte::parent() {
    return m_parent;
}

Contexte* Contexte::clear() {
    for (ISCObjectMapping::iterator it = m_objects.begin(); it != m_objects.end(); ++it) {
        delete it->second;
    }
    m_objects.clear();
    return this;
}
