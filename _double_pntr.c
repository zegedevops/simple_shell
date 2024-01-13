#include "shell.h"

/**
 * _double_pntr - frees malloced arrays
 * @str: array of string
 */
void _double_pntr(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
