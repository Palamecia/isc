#include "iscsourcemanager.h"
#include "Calcul/DataType/SystemInterface/iscsi.h"

#ifdef _WIN32
#define MODULE_SUFFIX   ".dll"
#else
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>
#define MODULE_SUFFIX   ".so"
#endif

#define MAX_BUFF    1024
#define ISCSI_PATH  String("/iscsi")

ISCSourceManager* ISCSourceManager::m_instance = NULL;

ISCSourceManager::ISCSourceManager() :
    m_defaultOutput("stdio") {
    char buff[MAX_BUFF];
#ifdef _WIN32
    GetCurrentDirectory(MAX_BUFF, buff);
    m_appRootPath = String(buff);
#else
    m_appRootPath = String(getcwd(buff, MAX_BUFF));
#endif
    m_iscRootPath = String(".");

    StringList interfaces = listFiles(m_appRootPath+ISCSI_PATH);
    for (uint i = 0; i < interfaces.size(); ++i) {
        Interface iscsi;
        iscsi.path = &m_appRootPath;
        iscsi.file = ISCSI_PATH + "/" + interfaces[i];
        iscsi.handle = NULL;
        m_systemInterfaces.insert(InterfaceMapping::value_type(interfaces[i].replace(MODULE_SUFFIX, ""), iscsi));
    }
}

void ISCSourceManager::init(int argc, char** argv) {

    if (m_instance) return;
    m_instance = new ISCSourceManager;

    for (int argn = 0; argn < argc; ++argn) {
        switch (argv[argn][0]) {
        case '-':
            switch (argv[argn][1]) {
            case 'o':
                m_instance->m_defaultOutput = String(argv[argn+1]);
                break;
            }
        default:
            m_instance->m_entryModule = String(argv[argn]);
        }
    }
}

ISCSourceManager *ISCSourceManager::instance() {
    return m_instance;
}

String ISCSourceManager::entryPointModule() {
    return m_entryModule;
}

StringList ISCSourceManager::args() {
    return m_args;
}

String ISCSourceManager::defaultOutput() {
    return m_defaultOutput;
}

StringList ISCSourceManager::moduleNames(const StringList& patern) {
    StringList modules;
    modules.append(patern.join());
    return modules;
}

String ISCSourceManager::modulePath(String module) {
    return m_appRootPath + "/" + module.replace(".", "/") + ".is";
}

/*File ISCSourceManager::openModuleFile(String module) {

}*/

StringList ISCSourceManager::listInterfaces() {
    StringList interfaces;
    InterfaceMapping::iterator it;
    for (it = m_systemInterfaces.begin(); it != m_systemInterfaces.end(); ++it) {
        interfaces.append(it->first);
    }
    return interfaces;
}

ISCSI* ISCSourceManager::loadInterface(const String &name) {
    InterfaceMapping::iterator itInterface = m_systemInterfaces.find(name);
    if (itInterface == m_systemInterfaces.end()) return NULL;

    Interface& interface = itInterface->second;
    if (interface.handle == NULL) {
#ifdef _WIN32

#else
        interface.handle = dlopen(String(*interface.path + interface.file).c_str(), RTLD_LAZY);
#endif
    }

    // dlerror();

    ISCSIBuilder iscsi_new =
#ifdef _WIN32

#else
            (ISCSIBuilder) dlsym(interface.handle, "iscsi_new");
#endif

    return (*iscsi_new)();
}

StringList ISCSourceManager::listFiles(const String &path) {
    StringList files;

#ifdef _WIN32

#else
    DIR *directory = opendir(path.c_str());
    if (!directory) return files;

    while (struct dirent *file = readdir(directory)) {
        String fileName = file->d_name;
        if (!fileName.startsWith(".")) files.append(fileName);
    }
    closedir(directory);
#endif

    return files;
}
