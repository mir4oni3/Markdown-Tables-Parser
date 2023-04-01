#include "Field.h"
#include <cstring>
#pragma warning (disable: 4996)
#include "Helpers.h"

void Field::setField(const char value[constants::FIELD_MAX_SYMBOLS]) {
	if (!helpers::contains(value, constants::FIELD_MAX_SYMBOLS, '\0')) {
		strcpy(this->value, constants::UNINITIALIZED_FIELD);
		return;
	}
	strcpy(this->value, value);
}

const char* Field::getField() const {
	return this->value;
}

Field::Field() {
	setField(constants::UNINITIALIZED_FIELD);
}

Field::Field(const char value[constants::FIELD_MAX_SYMBOLS]) {
	setField(value);
}