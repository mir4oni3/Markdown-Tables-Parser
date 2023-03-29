#pragma once
#include "Table.h"

class TableTool {
	Table table;
public:
	TableTool(const Table& table);
	void printLegend() const;
	void begin();
};
