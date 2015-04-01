#include "file.h"

File::File(const String& fileName) : m_fileName(fileName)
{}

bool File::open(OpenModeFlag flag) {
    std::fstream::open(m_fileName.c_str(), (ios_base::openmode)flag);
    return is_open();
}
