#include "stdio.h"
#include <cstdio>

#include "Calcul/iscobject.h"
#include "Calcul/DataType/Integer/integervalue.h"
#include "Calcul/DataType/Boolean/booleanvalue.h"
#include "Calcul/DataType/String/stringvalue.h"
#include "Calcul/DataType/None/voidvalue.h"
#include "Calcul/DataType/Null/nullvalue.h"
#include "Calcul/DataType/Error/errorvalue.h"

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
    else if (dynamic_pointer_cast<VoidValue>(object->value())) {
        printf("(none)");
    }
    else if (dynamic_pointer_cast<NullValue>(object->value())) {
        printf("(null)");
    }
    else if (ErrorValuePtr value = dynamic_pointer_cast<ErrorValue>(object->value())) {
        CallDumpList& stackDump = value->stack();
        for (int i = 0; i < stackDump.size(); ++i) {
            CallDump& call = stackDump[i];
            printf("%s:%d\n", call.module.c_str(), call.line+1);
            printf("\t%s\n", call.raw.c_str());
        }
        printf("%s\n", value->toText().c_str());
    }
}

void stdio::catchError(ISCObject *error) {
    execPrint(error);
}
