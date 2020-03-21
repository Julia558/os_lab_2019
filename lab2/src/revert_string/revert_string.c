#include "revert_string.h"

void RevertString(char *str)
{
	// your code here
    int length = strlen(str), i;
    char *s = (char *)malloc(sizeof(char)*length);
    for (i = 0; i < length; i++)
        s[i]=str[length-i-1];
    for (i = 0; i < length; i++)
        str[i]=s[i];
}

