#include "integervalue.h"
#include "Calcul/DataType/Function/builtinfunction.h"
#include "Calcul/DataType/Boolean/booleanvalue.h"
// color
// float
// string

// ############################################################################
// ##### operator :=
// ############################################################################
binary_operator(copy, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    lvalue->toInt() = rvalue->toInt();
    return self;
}
binary_operator(copy, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    lvalue->toInt() = rvalue->toBool();
    return self;
}
begin_operator_binding(copy, int)
    bind_binary_shape(int_type, copy_int_int);
    bind_binary_shape(bool_type, copy_int_int);
end_operator_binding;

// ############################################################################
// ##### operator !
// ############################################################################
unary_operator(not, int) {
    load_value(IntegerValue, rvalue, self);
    push_value(bool_type, new BooleanValue(!rvalue->toInt()));
}
begin_operator_binding(not, int)
    bind_unary_shape(not_int);
end_operator_binding;

// ############################################################################
// ##### operator +
// ############################################################################
unary_operator(add, int) {
    load_value(IntegerValue, rvalue, self);
    push_value(int_type, new IntegerValue(+rvalue->toInt()));
}
binary_operator(add, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() + rvalue->toInt()));
}
binary_operator(add, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() + rvalue->toBool()));
}
begin_operator_binding(add, int)
    bind_unary_shape(add_int);
    bind_binary_shape(int_type, add_int_int);
    bind_binary_shape(bool_type, add_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator -
// ############################################################################
unary_operator(sub, int) {
    load_value(IntegerValue, rvalue, self);
    push_value(int_type, new IntegerValue(-rvalue->toInt()));
}
binary_operator(sub, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() - rvalue->toInt()));
}
binary_operator(sub, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() - rvalue->toBool()));
}
begin_operator_binding(sub, int)
    bind_unary_shape(sub_int);
    bind_binary_shape(int_type, sub_int_int);
    bind_binary_shape(bool_type, sub_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator *
// ############################################################################
binary_operator(mult, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() * rvalue->toInt()));
}
binary_operator(mult, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() * rvalue->toBool()));
}
begin_operator_binding(mult, int)
    bind_binary_shape(int_type, mult_int_int);
    bind_binary_shape(bool_type, mult_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator /
// ############################################################################
binary_operator(div, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() / rvalue->toInt()));
}
binary_operator(div, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() / rvalue->toBool()));
}
begin_operator_binding(div, int)
    bind_binary_shape(int_type, div_int_int);
    bind_binary_shape(bool_type, div_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator %
// ############################################################################
binary_operator(mod, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() % rvalue->toInt()));
}
binary_operator(mod, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() % rvalue->toBool()));
}
begin_operator_binding(mod, int)
    bind_binary_shape(int_type, mod_int_int);
    bind_binary_shape(bool_type, mod_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator <
// ############################################################################
binary_operator(lt, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() < rvalue->toInt()));
}
binary_operator(lt, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() < rvalue->toBool()));
}
begin_operator_binding(lt, int)
    bind_binary_shape(int_type, lt_int_int);
    bind_binary_shape(bool_type, lt_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator >
// ############################################################################
binary_operator(gt, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() > rvalue->toInt()));
}
binary_operator(gt, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() > rvalue->toBool()));
}
begin_operator_binding(gt, int)
    bind_binary_shape(int_type, gt_int_int);
    bind_binary_shape(bool_type, gt_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator <=
// ############################################################################
binary_operator(lteq, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() <= rvalue->toInt()));
}
binary_operator(lteq, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() <= rvalue->toBool()));
}
begin_operator_binding(lteq, int)
    bind_binary_shape(int_type, lteq_int_int);
    bind_binary_shape(bool_type, lteq_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator >=
// ############################################################################
binary_operator(gteq, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() >= rvalue->toInt()));
}
binary_operator(gteq, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() >= rvalue->toBool()));
}
begin_operator_binding(gteq, int)
    bind_binary_shape(int_type, gteq_int_int);
    bind_binary_shape(bool_type, gteq_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator ==
// ############################################################################
binary_operator(eq, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() == rvalue->toInt()));
}
binary_operator(eq, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() == rvalue->toBool()));
}
begin_operator_binding(eq, int)
    bind_binary_shape(int_type, eq_int_int);
    bind_binary_shape(bool_type, eq_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator !=
// ############################################################################
binary_operator(ne, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() != rvalue->toInt()));
}
binary_operator(ne, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(bool_type, new BooleanValue(lvalue->toInt() != rvalue->toBool()));
}
begin_operator_binding(ne, int)
    bind_binary_shape(int_type, ne_int_int);
    bind_binary_shape(bool_type, ne_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator &
// ############################################################################
binary_operator(and, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() & rvalue->toInt()));
}
binary_operator(and, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() & rvalue->toBool()));
}
begin_operator_binding(and, int)
    bind_binary_shape(int_type, and_int_int);
    bind_binary_shape(bool_type, and_int_bool);
end_operator_binding;

// ############################################################################
// ##### operator |
// ############################################################################
binary_operator(or, int, int) {
    load_value(IntegerValue, lvalue, self);
    load_value(IntegerValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() | rvalue->toInt()));
}
binary_operator(or, int, bool) {
    load_value(IntegerValue, lvalue, self);
    load_value(BooleanValue, rvalue, args[0]);
    push_value(int_type, new IntegerValue(lvalue->toInt() | rvalue->toBool()));
}
begin_operator_binding(or, int)
    bind_binary_shape(int_type, or_int_int);
    bind_binary_shape(bool_type, or_int_bool);
end_operator_binding;
