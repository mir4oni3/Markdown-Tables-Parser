#include "TableTool.h"
#include <iostream>
#include <sstream>
#include "Constants.h"

TableTool::TableTool(const Table& table) {
	this->table.setTable(table);
}

void TableTool::printLegend() const{
	std::cout << "commands:" << std::endl;
	std::cout << "load <fileName> - loads contents from <fileName> into table" << std::endl;
	std::cout << "print - prints table into console" << std::endl;
	std::cout << "change <columnName> <newColumnName> - changes column name" << std::endl;
	std::cout << "addrow <field1> <field2> ... <fieldn> - adds row to table(if it has the same amount of fields as header)" << std::endl;
	std::cout << "change1 <rowNum> <columnName> <newCellValue> - changes cell value" << std::endl;
	std::cout << "change2 <columnName> <oldValue> <newValue> - changes cell value" << std::endl;
	std::cout << "select <columnName> <columnValue> - prints all rows that have <columnValue> in <columnName> column" << std::endl;
	std::cout << "save <fileName> - saves table in <fileName> file" << std::endl;
	std::cout << "exit - terminate the input" << std::endl;
}

void TableTool::begin() {
	while (true) {
		std::cout << "enter HELP for legend" << std::endl << ">";
		char input[256];
		std::cin.getline(input, 256);
		std::stringstream ss(input);
		char command[10];
		ss >> command;

		if (strcmp(command, "HELP") == 0) {
			printLegend();
			continue;
		}

		if (strcmp(command, "load") == 0) {
			char filename[32];
			ss >> filename;
			this->table.readFromFile(filename);
			continue;
		}

		if (strcmp(command, "print") == 0) {
			this->table.print();
			continue;
		}

		if (strcmp(command, "change") == 0) {
			char oldColumnName[constants::FIELD_MAX_SYMBOLS];
			char newColumnName[constants::FIELD_MAX_SYMBOLS];

			ss >> oldColumnName;
			ss >> newColumnName;

			this->table.changeHeaderField(oldColumnName, newColumnName);
			continue;
		}

		if (strcmp(command, "addrow") == 0) {
			Row row;
			char field[constants::FIELD_MAX_SYMBOLS];
			while (!ss.eof()) {
				ss >> field;
				if (field[0] == '\0') { break;  }
				row.addField(field);

			}
			this->table.addRow(row);
			continue;
		}

		if (strcmp(command, "change1") == 0) {
			int rowNum;
			char columnName[constants::FIELD_MAX_SYMBOLS];
			char newCellValue[constants::FIELD_MAX_SYMBOLS];

			ss >> rowNum;
			ss >> columnName;
			ss >> newCellValue;

			this->table.changeField(rowNum, columnName, newCellValue);
			continue;
		}

		if (strcmp(command, "change2") == 0) {
			char columnName[constants::FIELD_MAX_SYMBOLS];
			char oldValue[constants::FIELD_MAX_SYMBOLS];
			char newValue[constants::FIELD_MAX_SYMBOLS];

			ss >> columnName;
			ss >> oldValue;
			ss >> newValue;

			this->table.changeField(columnName,oldValue,newValue);
			continue;
		}

		if (strcmp(command, "select") == 0) {
			char columnName[constants::FIELD_MAX_SYMBOLS];
			char columnValue[constants::FIELD_MAX_SYMBOLS];

			ss >> columnName;
			ss >> columnValue;

			this->table.printCondition(columnName, columnValue);
			continue;
		}

		if (strcmp(command, "save") == 0) {
			char filename[32];
			ss >> filename;
			this->table.saveToFile(filename);
			continue;
		}

		if (strcmp(command, "exit") == 0) { 
			break; 
		}

	}
}