#include "Process/processmanager.h"
#include "System/iscsourcemanager.h"

int main(int argc, char *argv[]) {

    ISCSourceManager::init(argc, argv);

    ProcessManager process;
    process.setSourceFile(ISCSourceManager::instance()->entryPointModule());
    process.setDefaultOutput(ISCSourceManager::instance()->defaultOutput());

    process.exec();

    return process.checkExec();
}
