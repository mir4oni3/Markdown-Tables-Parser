#include "Table.h"
#include "Helpers.cpp"
#include <iostream>
#include <cstring>
#include <cmath>
#include <fstream>

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

void Table::changeField(int rowIndex, const char* columnName, const char* newName) { //rowIndex begins at 1
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

void addSpacesToSeparator(int colWidth, Row& separator) {
	for (int i = 0; i < separator.getFieldCount(); i++) {
		char curCell[FIELD_MAX_SYMBOLS];
		strcpy_s(curCell, FIELD_MAX_SYMBOLS, separator.getFieldAtIndex(i));
		bool startsWithColon = false, endsWithColon = false;
		startsWithColon = startsWith(curCell, ':'); endsWithColon = endsWith(curCell, ':');
		curCell[0] = ' ';
		curCell[1] = (startsWithColon) ? ':' : '-';
		for (int i = 2; i < colWidth - 2; i++) {
			curCell[i] = '-';
		}
		curCell[colWidth - 2] = (endsWithColon) ? ':' : '-';
		curCell[colWidth - 1] = ' ';
		curCell[colWidth] = '\0';
	}
}

void Table::addSpaces(int colWidth) {
	orientation* orientations = new orientation[this->header.getFieldCount()];
	fillOrientationsArray(orientations, this->rows[1]);
	addSpacesToSeparator(colWidth, this->rows[1]);

	for (int i = 0; i < this->currentRowCount; i++) {
		if (i == 1) {
			continue;
		}
		for (int j = 0; j < this->header.getFieldCount(); j++) {
			char* newCell = new char[colWidth + 1] {""};
			int freespaces = colWidth - strlen(this->rows[i].getFieldAtIndex(j));
			int freespacesL = 1, freespacesR = 1;
			freespaces -= 2;
			switch (orientations[j]) {
				case orientation::left: freespacesR += freespaces; break;
				case orientation::center: freespacesL += floor((double)freespaces / 2); freespacesR += ceil((double)freespaces / 2); break;
				case orientation::right: freespacesL += freespaces; break;
			}
			append(newCell, ' ', freespacesL);
			append(newCell, this->rows[i].getFieldAtIndex(j));
			append(newCell, ' ', freespacesR);
			this->rows[i].setFieldAtIndex(newCell, j);
			delete[] newCell;
		}
	}

	delete[] orientations;
}

void Table::print() {
	int colCount = this->header.getFieldCount();
	if (colCount == 0) {
		std::cout << "Empty table" << std::endl;
		return;
	}
	int colWidth = getLongestFieldLength() + 2;
	addSpaces(colWidth);

	for (int i = 0; i < this->currentRowCount; i++) {
		this->rows[i].printRow();
	}
}

void Table::printCondition(const char* columnName, const char* value) {
	int colCount = this->header.getFieldCount();
	if (colCount == 0) {
		std::cout << "Empty table" << std::endl;
		return;
	}
	int colWidth = getLongestFieldLength() + 2;
	addSpaces(colWidth);

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
		this->rows[i].printRow();
	}
}

void Table::saveToFile() const { 
	std::ofstream file(FILE_NAME); // default file name (inside Constants.h)
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