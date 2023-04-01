#include "Row.h"
#include <cstring>
#include "Helpers.h"
#include <iostream>

Row::Row(const Field fields[constants::MAX_COLUMN_COUNT], const bool isSeparator) {
	for (int i = 0; i < constants::MAX_COLUMN_COUNT; i++) {
		const char* tempfield = fields[i].getField();
		if (!isSeparator && strcmp(tempfield, constants::UNINITIALIZED_FIELD) == 0) {
			this->currentFieldCount = i;
		}
		this->fields[i].setField(tempfield);
	}
	this->isSeparator = isSeparator;
}

Row::Row(const bool isSeparator) {
	const char* value = (isSeparator) ? "-" : constants::UNINITIALIZED_FIELD;
	for (int i = 0; i < constants::MAX_COLUMN_COUNT; i++) {
		this->fields[i].setField(value);
	}
	this->currentFieldCount = 0;
	this->isSeparator = isSeparator;
}

const Row& Row::getRow() const {
	return *this;
}

const char* Row::getFieldAtIndex(const int index) const {
	if (index < 0 || index >= constants::MAX_COLUMN_COUNT) {
		return constants::UNINITIALIZED_FIELD;
	}
	return this->fields[index].getField();
}

int Row::getFieldCount() const {
	return this->currentFieldCount;
}

void Row::setRow(const Row& row) {
	for (int i = 0; i < constants::MAX_COLUMN_COUNT;i++) {
		this->fields[i].setField(row.getFieldAtIndex(i));
	}
	this->currentFieldCount = row.currentFieldCount;
	this->isSeparator = row.isSeparator;
}

void Row::setFieldAtIndex(const char* newValue, const int index) {
	if (index < 0 || index >= currentFieldCount) {
		return;
	}
	if (strlen(newValue) + 1 > constants::FIELD_MAX_SYMBOLS) {
		return;
	}
	if (!helpers::contains(newValue, constants::FIELD_MAX_SYMBOLS, '|')) {
		this->fields[index].setField(newValue);
	}
}

void Row::setFieldCount(const int fieldCount) {
	if (fieldCount < 0 || fieldCount >= constants::MAX_COLUMN_COUNT) {
		return;
	}
	this->currentFieldCount = fieldCount;
}

void Row::addField(const char* field) {
	if (field == nullptr || field[0] == '\0' || currentFieldCount == constants::MAX_COLUMN_COUNT) {
		return;
	}
	this->fields[currentFieldCount].setField(field);
	currentFieldCount++;
}

void Row::printRow() const {
	std::cout << "|";
	for (int i = 0; i < this->currentFieldCount; i++) {
		std::cout << this->getFieldAtIndex(i) << "|";
	}
	std::cout << std::endl;
}