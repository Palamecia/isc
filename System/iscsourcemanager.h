#ifndef ISCSOURCEMANAGER_H
#define ISCSOURCEMANAGER_H

#include "Util/list.h"
#include "Util/map.h"
#include "Util/string.h"
#include "Util/file.h"

class ISCSI;

class ISCSourceManager {
    struct Interface {
        String  *path;
        String  file;
        void    *handle;
    };
    typedef Map<String, Interface> InterfaceMapping;
public:

    static void init(int argc, char** argv);
    static ISCSourceManager *instance();

    String entryPointModule();
    StringList args();
    String defaultOutput();

    StringList moduleNames(const StringList& patern);
    String modulePath(String module);
    //File openModuleFile(String module);

    StringList listInterfaces();
    ISCSI* loadInterface(const String &name);

    static StringList listFiles(const String &path);

private:
    ISCSourceManager();
    static ISCSourceManager* m_instance;

    String m_appRootPath;
    String m_iscRootPath;

    String m_entryModule;
    StringList m_args;

    InterfaceMapping m_systemInterfaces;
    String m_defaultOutput;
};

#endif // ISCSOURCEMANAGER_H
