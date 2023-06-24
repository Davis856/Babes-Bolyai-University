#pragma once
#include "Country.h"

typedef enum {
	ADD,
	DELETE,
	UPDATE
} opType;

typedef struct {
	opType type;
	Country* c;
} Operation;

Operation* createOperation(opType type, Country* c);
void destroyOperation(Operation* o);

opType getOpType(Operation* o);
Country* getOpObject(Operation* o);