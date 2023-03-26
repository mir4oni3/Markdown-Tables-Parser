#pragma once
#include "Row.h"
#include "Constants.h"
#include <fstream>

class Table {
	Row header;
	Row rows[MAX_ROW_COUNT];
	unsigned currentRowCount = 0;
public:
	Table();
	Table(const Row& header);
	Table(const std::ifstream& file);

	void addRow(const Row& row);

	const Row& getRowAtIndex(const int index) const;
	const Row& getHeaderColumn() const;

	void setRowAtIndex(const Row& row, const int index);
	void setHeaderColumn(const Row& header);
	void setHeaderFieldAtIndex(const Field& newField, const int index);
	void changeField(const int rowIndex, const char* columnName, const char* newName); //rowIndex begins at 1
	void changeField(const char* columnName, const char* oldName, const char* newName); //changes only first instance

	void print() const;
	void printCondition(const char* columnName, const char* value) const;

	void saveToFile() const; // default file name (inside Constants.h)
};