#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cmdshel.h"

#define MAX_CMD_LEN 256
#define MAX_ARGS 10  /* Set an appropriate maximum num of argumtz */

/**
 * cust_token - Tokenizes the input command without using strtok
 * @cmd: The command to tokenize
 *
 * Return: An array of tokens (strings)
 */
char **cust_token(char *cmd)
{
	int r = 0;
	int arg_count = 0;
	int len = strlen(cmd);
	char **tokens;
	int start = 0;
	int end;
	int token_len;
/*	tokens[arg_count] = NULL; */
	/*int q; */

	tokens = malloc((MAX_ARGS + 1) * sizeof(char *)); /* Allocate memory token */
	if (!tokens)
	{
		perror("malloc");
			exit(EXIT_FAILURE);
	}
	/* Iterate the commd line and extract tokenz */
	while (r < len)
	{
		/* skip lead space */
		while (r < len && cmd[r] == ' ')
			r++;
		if (r == len)
			break;

		start = r;
		/* find the end of the current token */
		while (r < len && cmd[r] != ' ')
			r++;
		end = r;
		/* Extract the token */
		token_len = end - start;
		tokens[arg_count] = malloc((token_len + 1) * sizeof(char));
		if (!tokens[arg_count])
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strncpy(tokens[arg_count], &cmd[start], token_len);
		tokens[arg_count][token_len] = '\0';
		arg_count++;
		/* check if d maximum number of argumnt is reached */
		if (arg_count >= MAX_ARGS)
			break;
	}
/**
 *	for (q = 0; q < arg_count; q++)
 *   {
 *       free(tokens[q]);
 *   }
*/
	return (tokens);
}
