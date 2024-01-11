#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cmdshel.h"
#include <string.h>

/**
 * cmd_builting_shell - Handle the cd (change direct) builtin command.
 * @args: Array of strings containing d commd and itz argument.
 */

void cmd_builting_shell(char **args)
{
	int p_ret_z;
	char *direct;
	char *curr_direct = NULL;
	size_t size = 0;
	/* handle cd command */
	if (args[1] == NULL)
	{
		/* chang too d home direct */
		direct = getenv("HOME");
		if (direct == NULL)
		{
			fprintf(stderr, "Error: HOME environment variable not set\n");
			return;
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		/* handle cd - */
		direct = getenv("OLDPWD");
		if (direct == NULL)
		{
			fprintf(stderr, "Error: OLDPWD environment variable not set\n");
			return;
		}
	}
	else
	{
		/* chang to the spec direct */
		direct = args[1];
	}
	/* save the current directory in OLDPWD */
	curr_direct = getcwd(curr_direct, size);
	if (curr_direct == NULL)
	{
		perror("getcwd");
		return;
	}
	setenv("OLDPWD", curr_direct, 1);
	/* change to the specified directory */
	p_ret_z = chdir(direct);
	if (p_ret_z != 0)
	{
		perror("chdir");
		free(curr_direct);
		return;
	}
	setenv("PWD", curr_direct, 1);
	free(curr_direct);
	return;
}
