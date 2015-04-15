#include "iscsi.h"
#include "Calcul/DataType/SystemInterface/iscsidescriptror.h"

ISCSI::ISCSI() :
    BuiltinValue(NULL),
    m_printEnabeled(false) {
}

bool ISCSI::instanceOf(const TypeInfo& type) {

}

ISCObject *ISCSI::get(ISCObject *requester, const String& member) {

}

void ISCSI::print(ISCObject *object) {
    if (m_printEnabeled) execPrint(object);
}

String ISCSI::nextInstruction() {
    return String();
}

void ISCSI::catchError(ISCObject *) {}

void ISCSI::setPrintEnabeled(const bool enable) {
    m_printEnabeled = enable;
}

void ISCSI::execPrint(ISCObject *) {}
