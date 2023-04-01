#pragma once
#include "Constants.h"

class Field {
	char value[constants::FIELD_MAX_SYMBOLS];
public:
	void setField(const char value[constants::FIELD_MAX_SYMBOLS]);

	const char* getField() const;

	Field();
	Field(const char value[constants::FIELD_MAX_SYMBOLS]);
};