#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * newstr(const char * str) {
	int len = strlen(str);
	char * buff = (char *)malloc(len + 1);
	strcpy(buff, str);
	return buff;
}

void delstr(char * str) {
	free(str);
}

int search_in_string_array(char *strarr[], int maxlen, char *str) {
	int i;
	for (i = 0; i < maxlen && strarr[i]; i++)
		if (strcmp(strarr[i], str) == 0)
			return i;
	return -1;
}

int main () {
	char *strarr[32] = { 0 };

	strarr[0] = "this is const char *....";
	strarr[1] = (char *)malloc(1024);
	strcpy(strarr[1], "this is dynamic-allocated memory");
	strarr[2] = newstr("dynamic-allocated string from my function");
	strarr[3] = newstr("apple");

	int index = search_in_string_array(strarr,
			sizeof(strarr) / sizeof(strarr[0]), "apple");

	if (index > -1)
		printf("strarr[%d] = %s\n", index, strarr[index]);
	else
		printf("string not found.\n");

	free(strarr[1]); // remember to free
	delstr(strarr[2]);
	delstr(strarr[3]);

	return 0;
}
