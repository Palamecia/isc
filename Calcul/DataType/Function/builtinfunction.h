#ifndef BUILTINFUNCTION_H
#define BUILTINFUNCTION_H

#include "functionvalue.h"

class BuiltinFunction : public FunctionValue {
public:
    typedef ISCObject* (*Code)(ISCObject* self, const ISCObjectList& params);
    struct Shape {
        Shape(byte pc, TypeInfo ** pt, Code code) : pc(pc), pt(pt), code(code) {}
        byte pc;
        TypeInfo ** pt;
        Code code;
    };

    BuiltinFunction();
    virtual ~BuiltinFunction();

    ISCObject* run(ISCObject* self, const ISCObjectList& params);

protected:
    List<Shape> m_shapes;
};

#define load_value(type, name, object) \
    type##Ptr name = std::tr1::dynamic_pointer_cast<type>(object->value())
#define push_value(typeId, value) \
    ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[typeId]); \
    object->init(value); \
    return object
#define unary_operator(name, rvalue_t) \
    ISCObject* name##_##rvalue_t(ISCObject* self, const ISCObjectList&)
#define binary_operator(name, lvalue_t, rvalue_t) \
    ISCObject* name##_##lvalue_t##_##rvalue_t(ISCObject* self, const ISCObjectList& params)
#define bind_shape_0(code) \
    m_shapes.append(BuiltinFunction::Shape(0, NULL, &code))
#define bind_shape_1(type, code) \
    TypeInfo** pt_##type = new TypeInfo*[1]; \
    pt_##type[0] = new TypeInfo(type); \
    m_shapes.append(BuiltinFunction::Shape(1, pt_##type, &code))
#define begin_operator_binding(name, type) \
    class type##_##name##_operator : public BuiltinFunction { \
        public:type##_##name##_operator() {
#define end_operator_binding }}
#define bind_operator(set, type, name) \
ISCObject* type##_object = new ISCObject; \
type##_object->init(new type); \
set->insert(ISCObjectMapping::value_type(name, type##_object))

#endif // BUILTINFUNCTION_H
