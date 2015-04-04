#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

enum ErrorId {
    NULL_PTR,
    TYPE_DUPLICATION,
    MEMBER_DUPLICATION

};

class ISCObject;

#define raise_error throw makeError
ISCObject* makeError(ErrorId id, ...);

#endif // ERRORMANAGER_H
