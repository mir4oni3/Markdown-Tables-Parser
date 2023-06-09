#include <cstring>
#include "Helpers.h"

bool contains(const char* str, int length, char symbol) {
	for (int i = 0; i < length; i++) {
		if (str[i] == symbol) {
			return true;
		}
		if (str[i] == '\0') {
			break;
		}
	}
	return false;
}

bool startsWith(const char* str, char ch) {
	if (str[0] == ch) {
		return true;
	}
	return false;
}

bool endsWith(const char* str, char ch) {
	if (str[strlen(str) - 1] == ch) {
		return true;
	}
	return false;
}

void append(char* str, const char* str1) {
	int i = strlen(str);
	int j = 0;
	while (str1[j]) {
		str[i] = str1[j];
		j++;
		i++;
	}
	str[i] = '\0';
}

void append(char* str, char symbol, int count) {
	int i = strlen(str);
	for (int j = 0; j < count; j++) {
		str[i] = symbol;
		i++;
	}
	str[i] = '\0';
}

char* trim(char* str) {
	int i = 0;
	while (str[i] == ' ') {
		i++;
	}

	int j = strlen(str) - 1;
	while (str[j] == ' ') {
		j--;
	}

	for (int k = i; k <= j; k++) {
		str[k - i] = str[k];
	}

	str[j - i + 1] = '\0';
	return str;
}

int countOf(const char* str, const char ch) {
	int i = 0;
	int count = 0;
	while (str[i]) {
		if (str[i] == ch) {
			count++;
		}
		i++;
	}
	return count;
}