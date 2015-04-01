#ifndef TEXTSTREAM_H
#define TEXTSTREAM_H

#include "file.h"

class TextStream {
public:
    TextStream(File* file);

    String readAll();

private:
    File* m_file;
};

#endif // TEXTSTREAM_H
