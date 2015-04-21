#include "errormanager.h"

void errormanager_initmapping() {
    errormanager_mapError(NULL_PTR, "Null pointer");
    errormanager_mapError(UNEXPECTED_BLOC, "Unexpected '{' token");
    errormanager_mapError(EXPECTED_BLOC, "Expected '{' token");
    errormanager_mapError(TYPE_DUPLICATION, "Redefinition of type '%s.%s'");
    errormanager_mapError(MEMBER_DUPLICATION, "Redeclaration of '%s.%s'");
    errormanager_mapError(UNKNOWN_TOKEN, "Unknown tocken '%s'");
    errormanager_mapError(UNEXPECTED_TOKEN, "Unexpected tocken '%s'");
    errormanager_mapError(UNARY_INVALID_OPERANDS, "Invalid operand '%s' to unary operator '%s'");
    errormanager_mapError(BINARY_INVALID_OPERANDS, "Invalid operands '%s' and '%s' to binary operator '%s'");
    errormanager_mapError(UNKNOWN_MEMBER, "Class '%s' has no member named '%s'");
    errormanager_mapError(UNKNOWN_METHODE, "Class '%s' has no methode named '%s'");
    errormanager_mapError(UNEXPECTED_RETURN_TYPE, "Returned type is invalide, expecetd '%s'");
}

