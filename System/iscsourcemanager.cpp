#include "iscsourcemanager.h"
#include "Calcul/DataType/SystemInterface/iscsi.h"
#include <cstdio>
#include <cstring>

#ifdef _WIN32
#define PATH_SEP            "\\"
#define ISCSI_PATH          "\\iscsi"
#define INTERFACE_SUFFIX    ".dll"
#else
#include <unistd.h>
#include <dirent.h>
#include <dlfcn.h>

#define PATH_SEP            "/"
#define ISCSI_PATH          "/iscsi"
#define INTERFACE_SUFFIX    ".so"
#endif

#define MODULE_SUFFIX       ".is"
#define DEFAULT_MODULE      "stdio"
#define MAX_PATH            4096

ISCSourceManager* ISCSourceManager::m_instance = NULL;

ISCSourceManager::ISCSourceManager() : m_defaultOutput(DEFAULT_MODULE), m_entryModule(DEFAULT_MODULE) {
    char buff[MAX_PATH];
#ifdef _WIN32
    GetCurrentDirectory(MAX_PATH, buff);
    m_appRootPath = String(buff);
#else
    m_appRootPath = String(getcwd(buff, MAX_PATH));
#endif
}

ISCSourceManager::~ISCSourceManager() {
    InterfaceMapping::iterator it;
    for (it = m_systemInterfaces.begin(); it != m_systemInterfaces.end(); ++it) {
#ifdef _WIN32

#else
        dlclose(it->second.handle);
#endif
    }
}

void ISCSourceManager::init(int argc, char** argv) {

    if (m_instance) return;
    m_instance = new ISCSourceManager;

    char buff[MAX_PATH];
#ifdef _WIN32

#else
    size_t len = readlink(argv[0], buff, MAX_PATH);
    if (len < MAX_PATH) buff[len] = 0;
    else {
        strncpy(buff, argv[0], MAX_PATH);
        buff[MAX_PATH-1];
    }
#endif
    StringList iscRootPath = String(buff).split(PATH_SEP);
    iscRootPath.pop_back();
    m_instance->m_iscRootPath = iscRootPath.join(PATH_SEP);

    bool entryPointFound = false;

    for (int argn = 1; argn < argc; ++argn) {
        switch (argv[argn][0]) {
        case '-':
            switch (argv[argn][1]) {
            case 'o':
                m_instance->m_defaultOutput = String(argv[argn+1]);
                break;
            }
        default:
            if (!entryPointFound) {
                StringList sourcePath = String(argv[argn]).split(PATH_SEP);
                while (sourcePath.size() > 1) {
                    m_instance->m_appRootPath += PATH_SEP + sourcePath.first();
                    sourcePath.removeAt(0);
                }
                m_instance->m_entryModule = sourcePath.first().replace(MODULE_SUFFIX, "");
                entryPointFound = true;
            } else {
                m_instance->m_args.append(argv[argn]);
            }
        }
    }

    m_instance->findInterfaces(m_instance->m_appRootPath);
    m_instance->findInterfaces(m_instance->m_iscRootPath);
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
    String path;
    module.replace(".", PATH_SEP);

    path = m_appRootPath + PATH_SEP + module + MODULE_SUFFIX;
    if (FILE* file = fopen(path.c_str(), "r")) {
        fclose(file);
        return path;
    }
    path = m_iscRootPath + PATH_SEP + module + MODULE_SUFFIX;
    if (FILE* file = fopen(path.c_str(), "r")) {
        fclose(file);
        return path;
    }
    return String();
}

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

    ISCSIBuilder iscsi_new =
#ifdef _WIN32

#else
            (ISCSIBuilder) dlsym(interface.handle, "iscsi_new");
#endif

    return (*iscsi_new)();
}

void ISCSourceManager::findInterfaces(String &path) {
    StringList interfaces = listFiles(path+ISCSI_PATH);
    for (uint i = 0; i < interfaces.size(); ++i) {
        Interface iscsi;
        iscsi.path = &path;
        iscsi.file = ISCSI_PATH PATH_SEP + interfaces[i];
        iscsi.handle = NULL;
        m_systemInterfaces.insert(InterfaceMapping::value_type(interfaces[i].replace(INTERFACE_SUFFIX, ""), iscsi));
    }
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
