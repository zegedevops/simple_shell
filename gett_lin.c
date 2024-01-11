#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cmdshel.h"

#define MAX_INPUT_LEN 1024

/**
 * mi_get_lin - function implementation for gett_lin
 *
 * Return: dynamically allocat string with the input line
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_LEN 1024

char *mi_get_lin(void)
{
	char buffer[MAX_INPUT_LEN];
	int buffer_len = 0;
	char o;
	char *line;
	int r;

	while (1)
	{
		o = getchar();

		if (o == EOF || o == '\n')
		{
			break;
		}

		buffer[buffer_len++] = o;
		if (buffer_len >= MAX_INPUT_LEN - 1)
		{
			/* Buffer overflow prevention */
			fprintf(stderr, "input line too long\n");
			while ((o = getchar()) != '\n' && o != EOF)
				;
			break;
		}
	}

	if (buffer_len == 0 && o == EOF)
	{	
		return NULL;
	}
	line = malloc(buffer_len + 1);
	if (line == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (r = 0; r < buffer_len; r++)
	{
		line[r] = buffer[r];
	}
	line[buffer_len] = '\0';
	return line;
}
