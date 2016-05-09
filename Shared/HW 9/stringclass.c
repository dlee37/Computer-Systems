#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringclass.h"

struct string {
	char *word;
};

String String_new(char *str) {
	String newString = (String) malloc(sizeof(struct string));
	int len = strlen(str) + 1;
	newString->word = (char *) malloc(len * sizeof(char));
	strcpy(newString->word,str);
	return newString;
}

String String_concat(String s1, String s2){
	char *str1 = String_toCharArray(s1);
	char *str2 = String_toCharArray(s2);
	char *word = strcat(str1,str2);
	String s = String_new(word);
	return s;
}

void String_free(String s1) {
	free(s1->word);
	free(s1);
}

String String_copy(String s1) {
	char *word = String_toCharArray(s1);
	String s = String_new(word);
	return s;
}

char *String_toCharArray(String s1) {
	return s1->word;
}

int String_length(String s1) {
	char *str = String_toCharArray(s1);
	return strlen(str);
}

int String_compare(String s1, String s2) {
	char *str1 = String_toCharArray(s1);
	char *str2 = String_toCharArray(s2);
	return strcmp(str1,str2);
}