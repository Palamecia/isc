#include "integerdescriptor.h"
#include "integeroperator.h"

ISCObjectMapping* IntegerDescriptor::m_fcts = new ISCObjectMapping;

IntegerDescriptor::IntegerDescriptor() : TypeDescriptor(int_key_word) {
    TypeDescriptor::BuiltIn[int_type] = this;
    bind_operator(m_fcts, int_copy_operator, deep_copy_operator);
    bind_operator(m_fcts, int_not_operator, logical_not_operator);
    bind_operator(m_fcts, int_add_operator, add_operator);
    bind_operator(m_fcts, int_sub_operator, sub_operator);
    bind_operator(m_fcts, int_mult_operator, mult_operator);
    bind_operator(m_fcts, int_div_operator, div_operator);
    bind_operator(m_fcts, int_mod_operator, mod_operator);
    bind_operator(m_fcts, int_lt_operator, lt_operator);
    bind_operator(m_fcts, int_gt_operator, gt_operator);
    bind_operator(m_fcts, int_lteq_operator, lteq_operator);
    bind_operator(m_fcts, int_gteq_operator, gteq_operator);
    bind_operator(m_fcts, int_eq_operator, eq_operator);
    bind_operator(m_fcts, int_ne_operator, ne_operator);
    bind_operator(m_fcts, int_and_operator, logical_and_operator);
    bind_operator(m_fcts, int_or_operator, logical_or_operator);
}

void IntegerDescriptor::createInstance(ProcessManager*, const List<ISCObject*>& args, byte accesMask, ISCObject* instance) {
    IntegerValue* value = new IntegerValue(m_fcts);
    instance->init(value, accesMask);
}

IntegerValue* IntegerDescriptor::makeValue(const String& raw) {
    bool valide;
    int integer = raw.toInt(&valide);
    if (!valide) return NULL;
    IntegerValue* value = new IntegerValue(m_fcts, integer);
    return value;
}

IntegerValue* IntegerDescriptor::fromData(int data) {
    IntegerValue* value = new IntegerValue(m_fcts, data);
    return value;
}
