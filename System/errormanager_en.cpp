#include "errormanager.h"

void errormanager_initmapping() {
    errormanager_mapError(NULL_PTR, "Null pointer");
    errormanager_mapError(UNEXPECTED_BLOC, "Unexpected '{' token");
    errormanager_mapError(EXPECTED_BLOC, "Expected '{' token");
    errormanager_mapError(TYPE_DUPLICATION, "Redefinition of type '%s.%s'");
    errormanager_mapError(MEMBER_DUPLICATION, "Redeclaration of '%s.%s'");
    errormanager_mapError(UNKNOWN_TOKEN, "Unknown tocken '%s'");
    errormanager_mapError(UNARY_INVALID_OPERANDS, "Invalid operand '%s' to unary operator '%s'");
    errormanager_mapError(BINARY_INVALID_OPERANDS, "Invalid operands '%s' and '%s' to binary operator '%s'");
}
