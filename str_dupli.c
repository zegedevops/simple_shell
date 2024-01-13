#include "shell.h"

/**
 * str_dupli - return pointer to newly allocated space in mem,
 * which contains copy of the string given as a parameter
 * @str: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *str_dupli(char *str)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	while (*(str + len))
		len++;
	len++; /* add null terminator to length */

	duplicate_str = malloc(sizeof(char) * len); /* allocate memory */
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < len)
	{
		*(duplicate_str + i) = *(str + i);
		i++;
	}

	return (duplicate_str);
}
