#pragma once
#include "Constants.h"

class Field {
	char value[FIELD_MAX_SYMBOLS];
public:
	void setField(const char value[FIELD_MAX_SYMBOLS]);

	const char* getField() const;

	Field();
	Field(const char value[FIELD_MAX_SYMBOLS]);
};