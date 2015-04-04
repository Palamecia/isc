#include "errormanager.h"

#include "Calcul/iscobject.h"

ISCObject* makeError(ErrorId id, ...) {
    ISCObject* object = new ISCObject();

    return object;
}
