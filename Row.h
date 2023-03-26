#pragma once
#include "Field.h"

class Row {
	Field fields[MAX_COLUMN_COUNT];
	unsigned currentFieldCount = 0;
	bool isHeader = false;

public:
	Row(const Field fields[MAX_COLUMN_COUNT],const bool isHeader = false);
	Row();

	const Row& getRow() const;
	const char* getFieldAtIndex(const int index) const;

	void setRow(const Row& row);
	void setElementAtIndex(const char* newValue, const int index);
};