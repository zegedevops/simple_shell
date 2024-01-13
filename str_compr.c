#include "shell.h"

/**
 * str_compr - comparing two strings
 * @s1: first string
 * @s2: second string
 * Return: int tells num spaces in between, 0 if the same string
 */

int str_compr(char *s1, char *s2)
{
	int i = 0;

	while (*(s1 + i) == *(s2 + i) && *(s1 + i))
		i++;

	if (*(s2 + i))
		return (*(s1 + i) - *(s2 + i));
	else
		return (0);
}
