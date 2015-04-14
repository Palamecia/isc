#ifndef ISCPARSER_H
#define ISCPARSER_H

#include "dictionary.h"
#include "Util/list.h"
#include "Util/file.h"
#include "Util/textstream.h"

typedef unsigned int pos_t;
class ISCSI;

class ISCParser {
public:
    ISCParser();
    ISCParser(const String &module);
    ~ISCParser();

    Step* step(pos_t idx, Dictionary *dico);
    Step* nextStep(Dictionary* dico);

    inline uint line(pos_t idx) { return m_steps[idx]->line(); }
    inline String raw(pos_t idx) { return m_rawData[line(idx)]; }

    static bool isOperator(const String& op);
    static bool isWhiteSpace(const String& ws);
private:
    void updateCache(String data);
    String nextToken(bool &lineOver);
    String nextString(const String& delim, bool &lineOver);

    static StringList m_operators;
    bool m_commentMode;

    ISCSI* m_input;

    int m_rawLine;
    int m_rawColumn;
    StringList m_rawData;
    List<Step*> m_steps;
};

#endif // ISCPARSER_H
