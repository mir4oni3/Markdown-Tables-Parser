bool contains(const char* str,int length, char symbol) {
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
	int i = 0;
	while (str[i]) {
		i++;
	}
	if (str[i - 1] == ch) {
		return true;
	}
	return false;
}

void append(char* str, const char* str1) {
	int i = 0;
	while (str[i]) {
		i++;
	}
	int j = 0;
	while (str1[j]) {
		str[i] = str1[j];
		j++;
		i++;
	}
	str[i] = '\0';
}
void append(char* str, char symbol, int count) {
	int i = 0;
	while (str[i]) {
		i++;
	}
	for (int j = 0; j < count; j++) {
		str[i] = symbol;
		i++;
	}
	str[i] = '\0';
}