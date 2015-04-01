#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "step.h"
#include "Util/map.h"

typedef Map<String, StepFunctionPtr> MapKeyToInst;

class Dictionary {
public:
    Dictionary();
    Step* build(int line, const String& token);

private:
    MapKeyToInst m_keyToInst;
};

#endif // DICTIONARY_H
