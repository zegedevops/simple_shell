#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmdshel.h"

/**
 * exec_multi_commd - Execute multiple shell commands separated by ';'.
 * @cmd: Input command containing multiple commands separated by ';'.
 */
void exec_multi_commd(char *cmd, int *x_shel)
{
	char *command = NULL;
	char **commands = NULL;
	int r = 0;
	int num_commands = 0;
	char *ptr;
	char **command_args;
	int q;
	/* spilt the input command by ';' manually */
	for (ptr = cmd; *ptr != '\0'; ptr++)
	{
		if (*ptr == ';')
		{
			*ptr = '\0'; /* replace the ';' with null terminator */
			commands = realloc(commands, (num_commands + 1) * sizeof(char *));
			if (commands == NULL)
			{
				perror("realloc");
				return;
			}
			commands[num_commands] = command;
			num_commands++;
			command = NULL;
		}
		else
		{
			if (command == NULL)
			{
				command = ptr;
			}
		}
	}
	if (command != NULL)
	{
		commands = realloc(commands, (num_commands + 1) * sizeof(char *));
		if (commands == NULL)
		{
			perror("realloc");
			return;
		}
		commands[num_commands] = command;
		num_commands++;
	}
	/* Exec each individual command */
	for (r = 0; r < num_commands; r++)
	{
		command_args = cust_token(commands[r]);
		exec_shel_comnd(command_args, x_shel);
		for (q = 0; command_args[q] != NULL; q++)
		{
			free(command_args[q]);
		}
		free(command_args);
		r++;
	}
	free(commands);
}
