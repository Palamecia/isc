#include "errormanager.h"

void errormanager_initmapping() {
    errormanager_mapError(NULL_PTR, "");
    errormanager_mapError(UNEXPECTED_BLOC, "Unexpected '{' token");
    errormanager_mapError(EXPECTED_BLOC, "Expected '{' token");
    errormanager_mapError(TYPE_DUPLICATION, "");
    errormanager_mapError(MEMBER_DUPLICATION, "");
}
