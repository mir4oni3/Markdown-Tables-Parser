#pragma once

bool contains(const char* str, int length, char symbol);
bool startsWith(const char* str, char ch);
bool endsWith(const char* str, char ch);
void append(char* str, const char* str1);
void append(char* str, char symbol, int count);
char* trim(char* str);
int countOf(const char* str, const char ch);
