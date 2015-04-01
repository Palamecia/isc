#include "iscsidescriptror.h"
#include "System/iscsourcemanager.h"

ISCSIDescriptror::ISCSIDescriptror(const String &name)
    : TypeDescriptor(name)
{}

void ISCSIDescriptror::createInstance(ProcessManager* process, const List<ISCObject*>& params, byte accesMask, ISCObject* instance) {

    instance->init(ISCSourceManager::instance()->loadInterface(m_name), accesMask);

}
