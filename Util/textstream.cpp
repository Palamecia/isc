#include "textstream.h"
#include <sstream>

TextStream::TextStream(File* file) : m_file(file)
{}

String TextStream::readAll() {
    m_file->open(File::ReadOnly);
    std::stringstream buff;
    buff << m_file->rdbuf();
    m_file->close();
    return buff.str();
}
