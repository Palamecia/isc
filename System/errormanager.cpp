#include "errormanager.h"

#include "Calcul/iscobject.h"
#include "Calcul/DataType/Error/errordescriptor.h"
#include "Calcul/DataType/Error/errorvalue.h"

static ErrorMappin errorFormats = ErrorMappin();

ISCObject* errormanager_makeError(ErrorId id, ...) {
    const char *form = errorFormats[id].c_str();
    va_list arg;
    va_start(arg, form);

    String errorMessage;
    errorMessage.format(form, arg);

    ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[error_type]);
    object->init(ErrorDescriptor::fromData(errorMessage));
    return object;
}

void errormanager_mapError(ErrorId id, const String &format) {
    errorFormats.insert(ErrorMappin::value_type(id, format));
}
