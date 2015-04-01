#ifndef CALCUL_H
#define CALCUL_H

#include "Util/string.h"
#include "Util/stack.h"
#include "Util/list.h"

class ISCObject;
class MemoryManager;
typedef List<ISCObject*> ISCObjectList;

class Calcul {
public:
    class Offset {
    public:
        Offset() : begin(0), end(-1) {}
        Offset(int pos) : begin(pos), end(-1) {}
        int begin;
        int end;
    };
    struct OperatorSet {
        enum Grouping { LeftToRight, RightToLeft };
        enum Associativity { Unary, Binary, Both };
        StringList tockens;
        Grouping grouping;
        Associativity associativity;
        OperatorSet(StringList tockens, Grouping grouping, Associativity associativity)
            : tockens(tockens), grouping(grouping), associativity(associativity)
        {}
    };
    static const List<OperatorSet> operatorPrecedence;

    Calcul(const StringList& tokens);

    void startSubCalc(const int pos);
    void setSubCalcEnd(const int pos);

    void resolveUnary(int pos, const String& resultTocken);
    void resolveBinary(int pos, const String& resultTocken);
    bool resolveAndClose(const String& resultTocken);

    String& tocken(const int pos);
    int size();

    ISCObject* build(MemoryManager* memory);
    ISCObjectList resolve(MemoryManager* memory);

private:
    void firstResolution(MemoryManager *memory);
    void operatorResolution(MemoryManager* memory, const OperatorSet &operators);
    ISCObjectList lastResolution(MemoryManager *memory);

private:
    StringList m_tokens;
    Stack<Offset> m_offsets;
};

#endif // CALCUL_H
