#include "calcul.h"
#include "memorymanager.h"
#include "Process/iscparser.h"

const List<Calcul::OperatorSet> Calcul::operatorPrecedence = List<Calcul::OperatorSet>()
        << Calcul::OperatorSet(StringList()
                               << in_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Both)
        << Calcul::OperatorSet(StringList()
                               << add_operator
                               << sub_operator
                               << logical_not_operator
                               << adress_operator
                               << const_ref_operator, Calcul::OperatorSet::RightToLeft, Calcul::OperatorSet::Unary)
        << Calcul::OperatorSet(StringList()
                               << mult_operator
                               << div_operator
                               << mod_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << add_operator
                               << sub_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << lt_operator
                               << gt_operator
                               << lteq_operator
                               << gteq_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << eq_operator
                               << ne_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << logical_and_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << logical_or_operator, Calcul::OperatorSet::LeftToRight, Calcul::OperatorSet::Binary)
        << Calcul::OperatorSet(StringList()
                               << copy_operator
                               << deep_copy_operator, Calcul::OperatorSet::RightToLeft, Calcul::OperatorSet::Binary);

Calcul::Calcul(const StringList &tokens) {
    m_tokens = tokens;
    m_offsets.push(Offset());
}

void Calcul::startSubCalc(const int pos) {
    m_offsets.push(Offset(pos));
}

void Calcul::setSubCalcEnd(const int pos) {
    m_offsets.top().end = size() - pos;
}

void Calcul::resolveUnary(int pos, const String& resultTocken) {
    pos += m_offsets.top().begin;
    m_tokens.replace(pos, resultTocken);
    m_tokens.removeAt(pos + 1);
}

void Calcul::resolveBinary(int pos, const String& resultTocken) {
    pos += m_offsets.top().begin;
    m_tokens.replace(pos, resultTocken);
    m_tokens.removeAt(pos + 1);
    m_tokens.removeAt(pos - 1);
}

bool Calcul::resolveAndClose(const String& resultTocken) {
    int pos = m_offsets.pop().begin + 1;
    m_tokens.replace(pos, resultTocken);
    m_tokens.removeAt(pos + 1);
    m_tokens.removeAt(pos - 1);
    return !m_offsets.isEmpty();
}

String& Calcul::tocken(const int pos) {
    return m_tokens[m_offsets.top().begin + pos];
}

int Calcul::size() {
    Offset& offset = m_offsets.top();
    return m_tokens.size() - (offset.begin + (offset.end < 0 ? 0 : offset.end));
}

ISCObject* Calcul::build(MemoryManager* memory) {
    int pos = -1;
    TypeDescriptor* type = NULL;
    do {
        ++pos;
        type = memory->getType(tocken(pos++));
        if (!type) return NULL;

    } while (pos < size() && tocken(pos) == ".");

    TypeInfo::ModifierList modifiers;
    // Modifiers ...

    String name = (pos < size()) ? tocken(pos++) : String();

    ISCObjectList args;
    if (pos < size() && tocken(pos) == "(") {
        memory->createSubContexte();
        startSubCalc(pos);
        args = resolve(memory);
        resolveAndClose(String());
        memory->closeContexte();
    }

    // Resolve from 0 to pos
    for (int i = 0; i < pos; ++i) m_tokens.removeFirst();

    ISCObject* object = new ISCObject(TypeInfo(type, modifiers), name);
    object->construct(memory->m_process, args);
    m_tokens.prepend(object->name());
    return object;
}

ISCObjectList Calcul::resolve(MemoryManager* memory) {
    firstResolution(memory);
    for (uint i = 0; i < operatorPrecedence.size(); ++i) {
        operatorResolution(memory, operatorPrecedence[i]);
    }
    return lastResolution(memory);
}

void Calcul::firstResolution(MemoryManager* memory) {
    for (int pos = 0; pos < size(); ++pos) {

    }
}

void Calcul::operatorResolution(MemoryManager *memory, const OperatorSet& operators) {
    const OperatorSet::Grouping grp = operators.grouping;
    ISCObject* self = memory->getObject(this_key_word);
    for (int pos = (grp == OperatorSet::LeftToRight) ? 0 : size() - 1;
         grp == OperatorSet::LeftToRight ? pos < size() : pos >= 0;
         grp == OperatorSet::LeftToRight ? ++pos : --pos) {
        if (operators.tockens.contains(tocken(pos))) {
            ISCObject* rvalue = NULL;
            ISCObject* lvalue = NULL;
            ISCObject* result = NULL;
            switch (operators.associativity) {
            case OperatorSet::Binary:
                if (pos <= 0 || pos >= size()-1) break;
                lvalue = memory->getObject(tocken(pos-1));
                rvalue = memory->getObject(tocken(pos+1));
                result = lvalue->call(self, tocken(pos), ISCObjectList() << rvalue);
                memory->m_stack.push(result);
                resolveBinary(pos, result->name());
                break;
            case OperatorSet::Unary:
                if (pos >= size()-1) break;
                if (pos > 0 && !ISCParser::isOperator(tocken(pos-1))) continue;
                rvalue = memory->getObject(tocken(pos+1));
                result = rvalue->call(self, tocken(pos), ISCObjectList());
                memory->m_stack.push(result);
                resolveUnary(pos, result->name());
                break;
            case OperatorSet::Both:
                break;
            }
            if (operators.associativity != OperatorSet::Unary) {
                grp == OperatorSet::LeftToRight ? --pos : ++pos;
            }
        }
    }
}

ISCObjectList Calcul::lastResolution(MemoryManager* memory) {
    ISCObjectList results;
    for (int pos = 0; pos < size(); ++pos) {
        if (tocken(pos) == comma_operator) {
            results.append(new ISCObject(*memory->getObject(tocken(pos - 1))));
            resolveUnary(pos - 1, String());
            pos = 0;
        }
    }
    results.append(new ISCObject(*memory->getObject(tocken(0))));
    return results;
}
