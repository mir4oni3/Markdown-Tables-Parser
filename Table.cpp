#include "Table.h"
#include "Helpers.cpp"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>
#include <sstream>

Table::Table() {
	Row header;
	Row separator(true);
	this->addRow(header);
	this->addRow(separator);
	this->header.setRow(header);
	this->headerSeparator.setRow(separator);
}

Table::Table(const Row& header) {
	Row separator(true);
	separator.setFieldCount(header.getFieldCount());
	this->addRow(header);
	this->addRow(separator);
	this->header.setRow(header);
	this->headerSeparator.setRow(separator);
}

void Table::addRow(const Row& row) {
	if (this->currentRowCount = MAX_ROW_COUNT) {
		return;
	}
	if (row.getFieldCount() == 0 || (row.getFieldCount() != this->header.getFieldCount())) {
		return;
	}

	this->rows[currentRowCount].setRow(row);
	currentRowCount++;
}

const Row* Table::getRowAtIndex(const int index) const {
	if (index < 0 || index >= this->currentRowCount) {
		return nullptr;
	}
	return &(this->rows[index]);
}

void Table::setRowAtIndex(const int index, const Row& row) {
	if (index < 0 || index == 1 || index >= currentRowCount) {
		return;
	}

	if (row.getFieldCount() != this->header.getFieldCount() && this->header.getFieldCount() != 0) {
		return;
	}

	this->rows[index].setRow(row);
}

void Table::setHeaderRow(const Row& header) {
	if (header.getFieldCount() == 0) {
		return;
	}
	if (currentRowCount == 2) {
		this->setRowAtIndex(0, header);
		Row separator(true);
		separator.setFieldCount(header.getFieldCount());
		this->setRowAtIndex(1, separator);
		return;
	}
	if (header.getFieldCount() == this->header.getFieldCount()) {
		this->setRowAtIndex(0, header);
	}
}

void Table::changeHeaderField(const char* oldColumnName, const char* newColumnName) {
	if (oldColumnName == nullptr || newColumnName == nullptr || oldColumnName[0] == '\0' || newColumnName[0] == '\0') {
		return;
	}
	for (int i = 0; i < this->header.getFieldCount(); i++) {
		if (strcmp(this->header.getFieldAtIndex(i), oldColumnName) == 0) {
			this->header.setFieldAtIndex(newColumnName, i);
			break;
		}
	}
}

void Table::changeField(int rowIndex, const char* columnName, const char* newName) { //rowIndex begins at 1
	if (columnName == nullptr || newName == nullptr || columnName[0] == '\0' || newName[0] == '\0') {
		return;
	}
	rowIndex++;
	if (rowIndex < 2 || rowIndex >= this->currentRowCount) {
		return;
	}
	if (columnName == nullptr || newName == nullptr) {
		return;
	}
	int columnIndex = -1;
	for (int i = 0; i < header.getFieldCount(); i++) {
		if (strcmp(header.getFieldAtIndex(i), columnName) == 0) {
			columnIndex = i;
			break;
		}
	}
	if (columnIndex == -1) {
		return;
	}
	this->rows[rowIndex].setFieldAtIndex(newName, columnIndex);
}

void Table::changeField(const char* columnName, const char* oldName, const char* newName) { //changes only first instance
	if (columnName == nullptr || oldName == nullptr || newName == nullptr || 
		columnName[0] == '\0' || oldName[0] == '\0' || newName[0] == '\0') {
		return;
	}
	int columnIndex = -1;
	for (int i = 0; i < header.getFieldCount(); i++) {
		if (strcmp(header.getFieldAtIndex(i), columnName) == 0) {
			columnIndex = i;
			break;
		}
	}
	for (int i = 0; i < this->currentRowCount; i++) {
		if (strcmp(this->rows[i].getFieldAtIndex(columnIndex), oldName) == 0) {
			this->rows[i].setFieldAtIndex(newName, columnIndex);
			break;
		}
	}
}

int Table::getLongestFieldLength() const {
	int longest = 0;
	for (int i = 0; i < this->currentRowCount; i++) {
		if (i == 1) {
			continue;
		}
		for (int j = 0; j < this->header.getFieldCount(); j++) {
			int curlen = strlen(this->rows[i].getFieldAtIndex(j));
			if (curlen > longest) {
				longest = curlen;
			}
		}
	}
	return longest;
}

enum class orientation {
	left,
	center,
	right
};


void fillOrientationsArray(orientation* orientations, const Row& separator) {
	for (int i = 0; i < separator.getFieldCount(); i++) {
		const char* curField = separator.getFieldAtIndex(i);
		if (!contains(curField, FIELD_MAX_SYMBOLS, ':')) {
			orientations[i] = orientation::left;
			continue;
		}
		if (startsWith(curField, ':') && endsWith(curField, ':')) {
			orientations[i] = orientation::center;
			continue;
		}
		if (startsWith(curField, ':')) {
			orientations[i] = orientation::left;
			continue;
		}
		orientations[i] = orientation::right;
	}
}

void Table::print() {
	int colCount = this->header.getFieldCount();
	if (colCount == 0) {
		std::cout << "Empty table" << std::endl;
		return;
	}
	int colWidth = getLongestFieldLength();

	orientation* orientations = new orientation[this->header.getFieldCount()];
	fillOrientationsArray(orientations, this->rows[1]);

	for (int i = 0; i < this->currentRowCount; i++) {
		for (int j = 0; j < this->header.getFieldCount(); j++) {
			std::cout << "|";
			const char* currentField = this->rows[i].getFieldAtIndex(j);
			int remainingSpaces = colWidth - strlen(currentField);
			if (orientations[j] == orientation::left) {
				std::cout << currentField;
				for (int i = 0; i < remainingSpaces; i++) {
					std::cout << " ";
				}
			}
			if (orientations[j] == orientation::right) {
				for (int i = 0; i < remainingSpaces; i++) {
					std::cout << " ";
				}
				std::cout << currentField;
			}
			if (orientations[j] == orientation::center) {
				for (int i = 0; i <remainingSpaces / 2; i++) {
					std::cout << " ";
				}
				std::cout << currentField;
				int rightSpaces = (remainingSpaces % 2 == 0) ? remainingSpaces / 2 : (remainingSpaces / 2 + 1);
				for (int i = 0; i < rightSpaces; i++) {
					std::cout << " ";
				}
			}
		}
		std::cout << "|";
	}
}

void Table::printCondition(const char* columnName, const char* value) {
	if (columnName == nullptr || value == nullptr || columnName[0] == '\0' || value[0] == '\0') {
		return;
	}
	int colCount = this->header.getFieldCount();
	if (colCount == 0) {
		std::cout << "Empty table" << std::endl;
		return;
	}
	int colWidth = getLongestFieldLength();

	int columnIndex = -1;
	for (int i = 0; i < this->header.getFieldCount(); i++) {
		if (strcmp(this->header.getFieldAtIndex(i), columnName) == 0) {
			columnIndex = i;
			break;
		}
	}

	if (columnIndex == -1) {
		std::cout << "No column with this name" << std::endl;
		return;
	}

	for (int i = 0; i < this->currentRowCount; i++) {
		if (strcmp(this->rows[i].getFieldAtIndex(columnIndex), value) != 0) {
			continue;
		}
		orientation* orientations = new orientation[this->header.getFieldCount()];
		fillOrientationsArray(orientations, this->rows[1]);
		for (int j = 0; j < this->header.getFieldCount(); j++) {
			std::cout << "|";
			const char* currentField = this->rows[i].getFieldAtIndex(j);
			int remainingSpaces = colWidth - strlen(currentField);
			if (orientations[j] == orientation::left) {
				std::cout << currentField;
				for (int i = 0; i < remainingSpaces; i++) {
					std::cout << " ";
				}
			}
			if (orientations[j] == orientation::right) {
				for (int i = 0; i < remainingSpaces; i++) {
					std::cout << " ";
				}
				std::cout << currentField;
			}
			if (orientations[j] == orientation::center) {
				for (int i = 0; i < remainingSpaces / 2; i++) {
					std::cout << " ";
				}
				std::cout << currentField;
				int rightSpaces = (remainingSpaces % 2 == 0) ? remainingSpaces / 2 : (remainingSpaces / 2 + 1);
				for (int i = 0; i < rightSpaces; i++) {
					std::cout << " ";
				}
			}
		}
		std::cout << "|";
	}
}

void Table::saveToFile(const char* fileName) const { 
	if (fileName == nullptr || fileName[0] == '\0') {
		return;
	}
	std::ofstream file(fileName);
	if (!file.is_open()) {
		return;
	}
	for (int i = 0; i < this->currentRowCount; i++) {
		file << "|";
		for (int j = 0; j < this->header.getFieldCount(); j++) {
			file << this->rows[i].getFieldAtIndex(j) << "|";
		}
		file << std::endl;
	}
	file.close();
}

void Table::readFromFile(const char* fileName) {
	if (fileName == nullptr || fileName[0] == '\0') {
		return;
	}
	std::ifstream file(fileName);
	if (!file.is_open()) {
		return;
	}

	int ColumnCount = 0;
	char line[MAX_COLUMN_COUNT * (FIELD_MAX_SYMBOLS + 2)];
	int row = 0, col = 0;
	while (true) {
		file.getline(line, sizeof(line));
		if (line[0] == '\0') {
			break;
		}
		std::stringstream ss(line);
		ss.ignore();
		char current[FIELD_MAX_SYMBOLS * 2];
		while (true) {
			ss.getline(current, FIELD_MAX_SYMBOLS * 2, '|');
			trim(current);
			if (ss.eof()) {
				break;
			}
			this->rows[row].setFieldAtIndex(current, col);
			col++;
		}
		row++;
	}

	this->header.setRow(this->rows[0]);
	this->headerSeparator.setRow(this->rows[1]);
	this->currentRowCount = row;

	file.close();
}