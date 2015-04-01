#ifndef FILE_H
#define FILE_H

#include <fstream>
#include "string.h"

class File : public std::fstream {
public:
    enum OpenModeFlag {
        ReadOnly = std::ios_base::in,
        WriteOnly = std::ios_base::out,
        ReadWrite = std::ios_base::in + std::ios_base::out,
        Append = std::ios_base::app,
        Truncate = std::ios_base::trunc,
        Binary = std::ios_base::binary
    };

    File(const String& fileName);

    bool open(OpenModeFlag flag);

private:
    String m_fileName;
};

#endif // FILE_H
