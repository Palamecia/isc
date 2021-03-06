#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include "Util/map.h"
#include "Util/string.h"

enum ErrorId {
    NULL_PTR,
    UNEXPECTED_BLOC,
    EXPECTED_BLOC,
    TYPE_DUPLICATION,
    MEMBER_DUPLICATION,
    UNKNOWN_TOKEN,
    UNEXPECTED_TOKEN,
    UNARY_INVALID_OPERANDS,
    BINARY_INVALID_OPERANDS,
    UNKNOWN_MEMBER,
    UNKNOWN_METHODE,
    UNEXPECTED_RETURN_TYPE
};
typedef Map<ErrorId, String> ErrorMappin;

class ISCObject;

#define raise_error throw errormanager_makeError
ISCObject* errormanager_makeError(ErrorId id, ...);
void errormanager_initmapping();
void errormanager_mapError(ErrorId id, const String &format);

#endif // ERRORMANAGER_H
