#include "booleanvalue.h"
#include "Calcul/DataType/Integer/integervalue.h"
#include "Calcul/DataType/Function/builtinfunction.h"
// color
// float
// string

// ############################################################################
// ##### operator :=
// ############################################################################
binary_operator(copy, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    lvalue->toBool() = rvalue->toBool();
    return self;
}
binary_operator(copy, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    lvalue->toBool() = rvalue->toInt();
    return self;
}
begin_operator_binding(copy, bool)
    bind_binary_shape(bool_type, copy_bool_bool);
    bind_binary_shape(int_type, copy_bool_bool);
end_operator_binding;

// ############################################################################
// ##### operator !
// ############################################################################
unary_operator(not, bool) {
    load_value(BooleanValue, rvalue, self);
    push_value(int_type, BooleanDescriptor::fromData(!rvalue->toBool()));
}
begin_operator_binding(not, bool)
    bind_unary_shape(not_bool);
end_operator_binding;

// ############################################################################
// ##### operator +
// ############################################################################
unary_operator(add, bool) {
    load_value(BooleanValue, rvalue, self);
    push_value(bool_type, BooleanDescriptor::fromData(+rvalue->toBool()));
}
binary_operator(add, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() + rvalue->toBool()));
}
binary_operator(add, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() + rvalue->toInt()));
}
begin_operator_binding(add, bool)
    bind_unary_shape(add_bool);
    bind_binary_shape(bool_type, add_bool_bool);
    bind_binary_shape(int_type, add_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator -
// ############################################################################
unary_operator(sub, bool) {
    load_value(BooleanValue, rvalue, self);
    push_value(bool_type, BooleanDescriptor::fromData(-rvalue->toBool()));
}
binary_operator(sub, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() - rvalue->toBool()));
}
binary_operator(sub, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() - rvalue->toInt()));
}
begin_operator_binding(sub, bool)
    bind_unary_shape(sub_bool);
    bind_binary_shape(bool_type, sub_bool_bool);
    bind_binary_shape(int_type, sub_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator *
// ############################################################################
binary_operator(mult, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() * rvalue->toBool()));
}
binary_operator(mult, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() * rvalue->toInt()));
}
begin_operator_binding(mult, bool)
    bind_binary_shape(bool_type, mult_bool_bool);
    bind_binary_shape(int_type, mult_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator /
// ############################################################################
binary_operator(div, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() / rvalue->toBool()));
}
binary_operator(div, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() / rvalue->toInt()));
}
begin_operator_binding(div, bool)
    bind_binary_shape(bool_type, div_bool_bool);
    bind_binary_shape(int_type, div_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator %
// ############################################################################
binary_operator(mod, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() % rvalue->toBool()));
}
binary_operator(mod, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() % rvalue->toInt()));
}
begin_operator_binding(mod, bool)
    bind_binary_shape(bool_type, mod_bool_bool);
    bind_binary_shape(int_type, mod_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator <
// ############################################################################
binary_operator(lt, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() < rvalue->toBool()));
}
binary_operator(lt, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() < rvalue->toInt()));
}
begin_operator_binding(lt, bool)
    bind_binary_shape(bool_type, lt_bool_bool);
    bind_binary_shape(int_type, lt_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator >
// ############################################################################
binary_operator(gt, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() > rvalue->toBool()));
}
binary_operator(gt, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() > rvalue->toInt()));
}
begin_operator_binding(gt, bool)
    bind_binary_shape(bool_type, gt_bool_bool);
    bind_binary_shape(int_type, gt_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator <=
// ############################################################################
binary_operator(lteq, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() <= rvalue->toBool()));
}
binary_operator(lteq, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() <= rvalue->toInt()));
}
begin_operator_binding(lteq, bool)
    bind_binary_shape(bool_type, lteq_bool_bool);
    bind_binary_shape(int_type, lteq_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator >=
// ############################################################################
binary_operator(gteq, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() >= rvalue->toBool()));
}
binary_operator(gteq, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() >= rvalue->toInt()));
}
begin_operator_binding(gteq, bool)
    bind_binary_shape(bool_type, gteq_bool_bool);
    bind_binary_shape(int_type, gteq_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator ==
// ############################################################################
binary_operator(eq, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() == rvalue->toBool()));
}
binary_operator(eq, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() == rvalue->toInt()));
}
begin_operator_binding(eq, bool)
    bind_binary_shape(bool_type, eq_bool_bool);
    bind_binary_shape(int_type, eq_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator !=
// ############################################################################
binary_operator(ne, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() != rvalue->toBool()));
}
binary_operator(ne, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, BooleanDescriptor::fromData(lvalue->toBool() != rvalue->toInt()));
}
begin_operator_binding(ne, bool)
    bind_binary_shape(bool_type, ne_bool_bool);
    bind_binary_shape(int_type, ne_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator &
// ############################################################################
binary_operator(and, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() & rvalue->toBool()));
}
binary_operator(and, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() & rvalue->toInt()));
}
begin_operator_binding(and, bool)
    bind_binary_shape(bool_type, and_bool_bool);
    bind_binary_shape(int_type, and_bool_int);
end_operator_binding;

// ############################################################################
// ##### operator |
// ############################################################################
binary_operator(or, bool, bool) {
    load_value(BooleanValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() | rvalue->toBool()));
}
binary_operator(or, bool, int) {
    load_value(BooleanValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, BooleanDescriptor::fromData(lvalue->toBool() | rvalue->toInt()));
}
begin_operator_binding(or, bool)
    bind_binary_shape(bool_type, or_bool_bool);
    bind_binary_shape(int_type, or_bool_int);
end_operator_binding;
