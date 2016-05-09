#ifndef STRINGCLASS_H
#define STRINGCLASS_H

typedef struct string * String;

String String_new(char *str); //this creates a new string

String String_concat(String s1, String s2); //concatenates s1 with s2

void String_free(String s1); //frees the string so it becomes unusable

String String_copy(String s1); //copies a string onto another variable

char *String_toCharArray(String s1); //converts the string to a array of chars

int String_length(String s1); //returns the length of the string

int String_compare(String s1, String s2); //strcmp the two items

#endif