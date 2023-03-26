#include "Field.h"
#include <cstring>
#pragma warning (disable: 4996)
#include "Helpers.cpp"

void Field::setField(const char value[FIELD_MAX_SYMBOLS]) {
	if (!contains(value, FIELD_MAX_SYMBOLS, '\0')) {
		strcpy(this->value, UNINITIALIZED_FIELD);
		return;
	}
	strcpy(this->value, value);
}

const char* Field::getField() const {
	return this->value;
}

Field::Field() {
	setField(UNINITIALIZED_FIELD);
}

Field::Field(const char value[FIELD_MAX_SYMBOLS]) {
	setField(value);
}