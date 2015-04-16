#include "errormanager.h"

#include "Calcul/iscobject.h"
#include "Calcul/DataType/Error/errordescriptor.h"
#include "Calcul/DataType/Error/errorvalue.h"

#include <cstdio>

static ErrorMappin errorFormats = ErrorMappin();

ISCObject* errormanager_makeError(ErrorId id, ...) {
    char buff[1024];

    va_list arg;
    va_start(arg, id);
    vsprintf(buff, errorFormats[id].c_str(), arg);
    va_end(arg);

    ISCObject* object = new ISCObject(TypeDescriptor::BuiltIn[error_type]);
    object->init(ErrorDescriptor::fromData(buff));
    return object;
}

void errormanager_mapError(ErrorId id, const String &format) {
    errorFormats.insert(ErrorMappin::value_type(id, format));
}
