#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Operation.h"
#include "Country.h"

Operation* createOperation(opType type, Country* c) {
	Operation* op = (Operation*)malloc(sizeof(Operation));
	op->type = type;

	Country* copyOfC = copyCountry(c);
	op->c = copyOfC;

	return op;
}

void destroyOperation(Operation* o) {
	if (o == NULL)
		return;

	destroyCountry(o->c);
	free(o);
}

opType getOpType(Operation* o) {
	if (o == NULL)
		return -1;
	return o->type;
}

Country* getOpObject(Operation* o) {
	if (o == NULL)
		return NULL;
	return o->c;
}
