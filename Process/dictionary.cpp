#include "dictionary.h"
#include "processmanager.h"

Dictionary::Dictionary() {
    m_keyToInst.insert(MapKeyToInst::value_type(chevron_open_tocken,    &ProcessManager::stepBalise));
    m_keyToInst.insert(MapKeyToInst::value_type(break_tocken,           &ProcessManager::stepBreak));
    m_keyToInst.insert(MapKeyToInst::value_type(case_tocken,            &ProcessManager::stepCase));
    m_keyToInst.insert(MapKeyToInst::value_type(catch_tocken,           &ProcessManager::stepCatch));
    m_keyToInst.insert(MapKeyToInst::value_type(class_tocken,           &ProcessManager::stepClass));
    m_keyToInst.insert(MapKeyToInst::value_type(continue_tocken,        &ProcessManager::stepContinue));
    m_keyToInst.insert(MapKeyToInst::value_type(default_tocken,         &ProcessManager::stepDefault));
    m_keyToInst.insert(MapKeyToInst::value_type(else_tocken,            &ProcessManager::stepElse));
    m_keyToInst.insert(MapKeyToInst::value_type(block_close_operator,   &ProcessManager::stepEnd));
    m_keyToInst.insert(MapKeyToInst::value_type(enum_tocken,            &ProcessManager::stepEnum));
    m_keyToInst.insert(MapKeyToInst::value_type(for_tocken,             &ProcessManager::stepFor));
    m_keyToInst.insert(MapKeyToInst::value_type(if_tocken,              &ProcessManager::stepIf));
    m_keyToInst.insert(MapKeyToInst::value_type(load_tocken,            &ProcessManager::stepLoad));
    m_keyToInst.insert(MapKeyToInst::value_type(public_tocken,          &ProcessManager::stepVisibility));
    m_keyToInst.insert(MapKeyToInst::value_type(print_tocken,           &ProcessManager::stepPrint));
    m_keyToInst.insert(MapKeyToInst::value_type(private_tocken,         &ProcessManager::stepVisibility));
    m_keyToInst.insert(MapKeyToInst::value_type(property_tocken,        &ProcessManager::stepVisibility));
    m_keyToInst.insert(MapKeyToInst::value_type(protected_tocken,       &ProcessManager::stepVisibility));
    m_keyToInst.insert(MapKeyToInst::value_type(return_tocken,          &ProcessManager::stepReturn));
    m_keyToInst.insert(MapKeyToInst::value_type(static_tocken,          &ProcessManager::stepVisibility));
    m_keyToInst.insert(MapKeyToInst::value_type(switch_tocken,          &ProcessManager::stepSwitch));
    m_keyToInst.insert(MapKeyToInst::value_type(throw_tocken,           &ProcessManager::stepThrow));
    m_keyToInst.insert(MapKeyToInst::value_type(try_tocken,             &ProcessManager::stepTry));
    m_keyToInst.insert(MapKeyToInst::value_type(yield_tocken,           &ProcessManager::stepYield));
    m_keyToInst.insert(MapKeyToInst::value_type(while_tocken,           &ProcessManager::stepWhile));
}

Step* Dictionary::build(int line, const String& token) {
    MapKeyToInst::iterator it = m_keyToInst.find(token);
    Step* step = NULL;
    if (it == m_keyToInst.end()) {
        // Step de calcule
        step = new Step(line, &ProcessManager::stepCalc);
        step->addToken(token);
    } else {
        step = new Step(line, it->second);
        if (it->second == &ProcessManager::stepVisibility) {
            step->addToken(token);
        }
    }
    return step;
}
