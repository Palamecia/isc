#include "booleandescriptor.h"
#include "booleanoperator.h"

ISCObjectMapping* BooleanDescriptor::m_fcts = new ISCObjectMapping;

BooleanDescriptor::BooleanDescriptor() : TypeDescriptor(bool_key_word) {
    TypeDescriptor::BuiltIn[bool_type] = this;
    bind_operator(m_fcts, bool_copy_operator, deep_copy_operator);
    bind_operator(m_fcts, bool_not_operator, logical_not_operator);
    bind_operator(m_fcts, bool_add_operator, add_operator);
    bind_operator(m_fcts, bool_sub_operator, sub_operator);
    bind_operator(m_fcts, bool_mult_operator, mult_operator);
    bind_operator(m_fcts, bool_div_operator, div_operator);
    bind_operator(m_fcts, bool_mod_operator, mod_operator);
    bind_operator(m_fcts, bool_lt_operator, lt_operator);
    bind_operator(m_fcts, bool_gt_operator, gt_operator);
    bind_operator(m_fcts, bool_lteq_operator, lteq_operator);
    bind_operator(m_fcts, bool_gteq_operator, gteq_operator);
    bind_operator(m_fcts, bool_eq_operator, eq_operator);
    bind_operator(m_fcts, bool_ne_operator, ne_operator);
    bind_operator(m_fcts, bool_and_operator, logical_and_operator);
    bind_operator(m_fcts, bool_or_operator, logical_or_operator);
}

void BooleanDescriptor::createInstance(ProcessManager* process, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    BooleanValue* value = new BooleanValue(m_fcts);
    instance->init(value, accesMask);
}

BooleanValue* BooleanDescriptor::makeValue(const String& raw) {
    BooleanValue* value = NULL;
    if (raw == true_key_word) {
        value = new BooleanValue(m_fcts, true);
    }
    if (raw == false_key_word) {
        value = new BooleanValue(m_fcts, false);
    }
    return value;
}

BooleanValue* BooleanDescriptor::fromData(bool data) {
    BooleanValue* value = new BooleanValue(m_fcts, data);
    return value;
}
