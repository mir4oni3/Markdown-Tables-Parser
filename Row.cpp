#include "Row.h"
#include <cstring>
#include "Helpers.cpp"

Row::Row(const Field fields[MAX_COLUMN_COUNT], const bool isHeader = false) {
	for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
		const char* tempfield = fields[i].getField();
		if (strcmp(tempfield, UNINITIALIZED_FIELD) == 0) {
			this->currentFieldCount = i;
		}
		this->fields[i].setField(tempfield);
	}
	this->isHeader = isHeader;
}

Row::Row() {
	for (int i = 0; i < MAX_COLUMN_COUNT; i++) {
		this->fields[i].setField(UNINITIALIZED_FIELD);
	}
	this->currentFieldCount = 0;
	this->isHeader = false;
}

const Row& Row::getRow() const {
	return *this;
}

const char* Row::getFieldAtIndex(const int index) const {
	if (index < 0 || index >= MAX_COLUMN_COUNT) {
		return UNINITIALIZED_FIELD;
	}
	return this->fields[index].getField();
}

void Row::setRow(const Row& row) {
	for (int i = 0; i < MAX_COLUMN_COUNT;i++) {
		this->fields[i].setField(row.getFieldAtIndex(i));
	}
	this->currentFieldCount = row.currentFieldCount;
	this->isHeader = row.isHeader;
}

void Row::setElementAtIndex(const char* newValue, const int index) {
	if (index < 0 || index >= currentFieldCount) {
		return;
	}
	if (strlen(newValue) + 1 > FIELD_MAX_SYMBOLS) {
		return;
	}
	this->fields[index].setField(newValue);
}