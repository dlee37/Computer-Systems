#include <stdio.h>
#include "stringclass.h"

int main() {
	String s1 = String_new("abcd");
	String s2 = String_new("xyz");
	String s3 = String_concat(s1, s2);
	String_free(s1);
	String s4 = String_copy(s2);
	String_free(s2);
	char *c1 = String_toCharArray(s3);
	char *c2 = String_toCharArray(s4);
	if (String_length(s3) > String_length(s4))
		printf("%s is longer than %s\n", c1, c2);
	else
		printf("%s is longer than %s\n", c2, c1);

	if (String_compare(s3, s4) > 0)
		printf("%s is greater than %s\n", c1, c2);
	else if (String_compare(s3, s4) < 0)
		printf("%s is greater than %s\n", c2, c1);
	else
		printf("%s and %s are the same\n", c2, c1);
}



	
