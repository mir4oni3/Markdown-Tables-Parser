#pragma once
#include "Field.h"

class Row {
	Field fields[constants::MAX_COLUMN_COUNT];
	int currentFieldCount = 0;
	bool isSeparator = false;

public:
	Row(const Field fields[constants::MAX_COLUMN_COUNT], const bool isSeparator = false);
	Row(const bool isSeparator = false);

	const Row& getRow() const;
	const char* getFieldAtIndex(const int index) const;
	int getFieldCount() const;

	void setRow(const Row& row);
	void setFieldAtIndex(const char* newValue, const int index);
	void setFieldCount(const int fieldCount);

	void addField(const char* field);

	void printRow() const;
};