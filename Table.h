#pragma once
#include "Row.h"
#include "Constants.h"
#include <fstream>

class Table {
	Row header;
	Row headerSeparator;
	Row rows[MAX_ROW_COUNT];
	int currentRowCount = 0;

	int getLongestFieldLength() const;
public:
	Table();
	Table(const Row& header);

	void addRow(const Row& row);

	const Row* getRowAtIndex(const int index) const;

	void setRowAtIndex(const int index, const Row& row);
	void setHeaderRow(const Row& header);
	void changeHeaderField(const char* oldColumnName, const char* newColumnName);
	void changeField(int rowIndex, const char* columnName, const char* newName); //rowIndex begins at 1
	void changeField(const char* columnName, const char* oldName, const char* newName); //changes only first instance

	void print();
	void printCondition(const char* columnName, const char* value);

	void saveToFile(const char* fileName) const;
	void readFromFile(const char* fileName);
};