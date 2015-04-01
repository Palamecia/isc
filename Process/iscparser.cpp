#include "iscparser.h"
#include "System/iscsourcemanager.h"
#include "Calcul/DataType/SystemInterface/iscsi.h"
#include "Util/typedefs.h"
#include "Syntax.h"

StringList ISCParser::m_operators = StringList()
        << "//" << "/*" << "*/"
        << "'" << "\"" << "\\" << "\\'" << "\\\""
        << ":"
        << "++" << "--"
        << "."
        << "(" << ")" << "[" << "]" << "[]" << "{" << "}" << "{}"
        << "!"
        << "+" << "-"
        << "$" << "@"
        << "*" << "/" << "%"
        << "<" << ">" << "<=" << ">="
        << "=" << ":="
        << "==" << "!="
        << "&" << "|"
        << "+=" << "-=" << "*=" << "/=" << "%=" << "&=" << "|="
        << "," << ";";

ISCParser::ISCParser()
    : m_commentMode(false),
      m_input(NULL),
      m_rawLine(0),
      m_rawColumn(0)
{}

ISCParser::~ISCParser() {
    for (uint i = 0; i < m_steps.size(); ++i) delete m_steps[i];
}

ISCParser::ISCParser(const String &module)
    : m_commentMode(false), m_input(NULL), m_rawLine(0), m_rawColumn(0) {

    File file(ISCSourceManager::instance()->modulePath(module));
    file.open(File::ReadOnly);
    TextStream stream(&file);

    updateCache(stream.readAll());
    while (m_rawData[m_rawLine].startsWith("#!")) ++m_rawLine;

    // "//.*?\\n")
    // "/\\*([^*]|[\\n]|(\\*+([^*/]|[\\n])))*\\*+/"
}

ISCParser::ISCParser(ISCSI* input)
    : m_commentMode(false), m_input(input), m_rawLine(0), m_rawColumn(0) {
    updateCache(m_input->nextInstruction());
}

Step* ISCParser::step(pos_t idx, Dictionary* dico) {
    if (idx < (pos_t)m_steps.size()) return m_steps[idx];
    if (idx == (pos_t)m_steps.size()) return nextStep(dico);
    // TODO : Erreur
    return NULL;
}

Step* ISCParser::nextStep(Dictionary *dico) {
    if (m_rawLine >= m_rawData.size()) return NULL;

    const int stepLine = m_rawLine; bool lineOver;
    String tokenType = nextToken(lineOver);
    if (tokenType.isEmpty()) { // Gestion des lignes vides
        return nextStep(dico);
    }

    Step *step = dico->build(stepLine, tokenType);
    if (tokenType == block_close_operator) { // Gestion des fin d'instructions
        m_steps.append(step);
        return step;
    }

    while (!lineOver) {
        String token = nextToken(lineOver);
        if (token == block_open_operator) {
            step->createContexte();
            break;
        }
        if (token == semicolon_operator) {
            break;
        }
        else if (token == block_close_operator) {
            m_steps.append(step);
            m_steps.append(dico->build(stepLine, token));
            return step;
        }
        else if(lineOver && token == back_slash_operator) {
            lineOver = false;
        }
        else if (token == "++") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("+");
            step->addToken("1");
        }
        else if (token == "--") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("-");
            step->addToken("1");
        }
        else if (token == "+=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("+");
        }
        else if (token == "-=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("-");
        }
        else if (token == "*=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("*");
        }
        else if (token == "/=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("/");
        }
        else if (token == "%=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("%");
        }
        else if (token == "&=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("&");
        }
        else if (token == "|=") {
            String lastToken = step->lastToken();
            step->addToken("=");
            step->addToken(lastToken);
            step->addToken("|");
        }
        else if (!token.isEmpty()) {
            step->addToken(token);
        }
    }

    m_steps.append(step);
    return step;

}

void ISCParser::updateCache(String data) {
    data.replace("\r\n", "\n");
    data.replace("\r", "\n");
    m_rawData.append(data.split("\n"));
}

String ISCParser::nextToken(bool& lineOver) {

    if (m_rawLine > m_rawData.size()) {
        // TODO : Erreur unexpected end of file
    }

    const int lineSize = m_rawData[m_rawLine].size();
    while (isWhiteSpace(String(m_rawData[m_rawLine][m_rawColumn])) && m_rawColumn < lineSize) ++m_rawColumn;

    bool mode_operator = isOperator(String(m_rawData[m_rawLine][m_rawColumn]));

    String token;
    while (m_rawColumn < lineSize) {
        Char ch = m_rawData[m_rawLine][m_rawColumn];
        if (mode_operator) {
            if (isOperator(token + ch)) token += ch;
            else break;
        } else {
            if (isOperator(ch)) break;
            else if (isWhiteSpace(ch)) break;
            else token += ch;
        }
        ++m_rawColumn;
    }

    if (!m_commentMode) {
        // Gestion des chaines
        if (token == "'" || token == "\"") {
            return nextString(token, lineOver);
        }

        // Gestion des comentaires
        if (token == "//") {
            m_rawColumn = 0;
            ++m_rawLine;
            return nextToken(lineOver);
        }
        if (token == "/*") {
            m_commentMode = true;
            while (nextToken(lineOver) != "*/");
            m_commentMode = false;
            return nextToken(lineOver);
        }
    }

    if ((lineOver = (m_rawColumn >= lineSize - 1))) {
        m_rawColumn = 0;
        ++m_rawLine;
    }
    return token;
}

String ISCParser::nextString(const String& delim, bool &lineOver) {
    String token = delim;

    int lineSize = m_rawData[m_rawLine].size();
    while (m_rawColumn < lineSize) {
        // Lecture de la chaine
        Char ch = m_rawData[m_rawLine][m_rawColumn];
        ++m_rawColumn;
        if ((lineOver = (m_rawColumn >= lineSize - 1))) {
            m_rawColumn = 0;
            ++m_rawLine;
        }

        // Traitement du caractère
        if (lineOver && ch == '\\') {
            lineSize = m_rawData[m_rawLine].size();
        } else {
            token += ch;
        }
        if (delim == ch) break;
    }

    return token;
}

bool ISCParser::isOperator(const String& op) {
    return m_operators.contains(op);
}

bool ISCParser::isWhiteSpace(const String& ws) {
    return ws == " " || ws == "\t"; // TODO utiliser méthode string
}
