#include "stdio.h"
#include <cstdio>

#include "Calcul/iscobject.h"
#include "Calcul/DataType/Integer/integervalue.h"
#include "Calcul/DataType/Boolean/booleanvalue.h"
#include "Calcul/DataType/String/stringvalue.h"

stdio::stdio() {
    setPrintEnabeled(true);
}

stdio::~stdio() {

}

String stdio::nextInstruction() {
    size_t size = 1024;
    char *buff = new char[size];

    printf("\n%s> ", "isc");
    getline(&buff, &size, stdin);

    String instruction = buff;
    delete [] buff;
    return instruction;
}

void stdio::execPrint(ISCObject* object) {
    using namespace std::tr1;
    if (IntegerValuePtr value = dynamic_pointer_cast<IntegerValue>(object->value())) {
        printf("%d", value->toInt());
    }
    else if (BooleanValuePtr value = dynamic_pointer_cast<BooleanValue>(object->value())) {
        printf("%s", value->toBool() ? "true" : "false");
    }
    else if (StringValuePtr value = dynamic_pointer_cast<StringValue>(object->value())) {
        printf("%s", value->toString().c_str());
    }
}
