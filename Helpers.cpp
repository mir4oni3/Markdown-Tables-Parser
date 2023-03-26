bool contains(const char* str,int length, char symbol) {
	for (int i = 0; i < length; i++) {
		if (str[i] == symbol) {
			return true;
		}
	}
	return false;
}