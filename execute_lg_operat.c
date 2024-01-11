#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cmdshel.h"
#include <stdio.h>
#define MAX_SUB_COMMANDS 100

/**
 * execute_lg_operat - Executes a sub-command based on logical operators (&& and ||).
 *
 * @sub_cmd: The sub-command to be executed.
 * @prev_status: The status of d previous commd exec.
 *
 * Return: The exit status for sub-command exec.
 */
int execute_lg_operat(const char *sub_cmd, bool *x_shel)
{
	int status = 0;
	bool and_operator = false;
	bool or_operator = false;
	char *zubb_cmmd_kopi;
	int exit_shell_int = x_shel ? 1 : 0;

	zubb_cmmd_kopi= strdup(sub_cmd);
	if (zubb_cmmd_kopi == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	/* determine if the command is followed by && */
	if (zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) -2] == '&' && zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) - 1] == '&')
	{
		and_operator = true;
		zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) - 2] = '\0'; /* remove the && */
	}

	/* Determine if the command is followed by || */
	if (zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) - 2] == '|' && zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) - 1] == '|')
	{
		or_operator = true;
		zubb_cmmd_kopi[strlen(zubb_cmmd_kopi) - 2] = '\0'; /* remove the || */
	}
	/* Execute the sub-command and get its exit status */
	 exec_shel_comnd(cust_token(zubb_cmmd_kopi), &exit_shell_int);
	if ((status == 0 && and_operator) || (status != 0 && or_operator))
	{
		*x_shel = false;
	}
	return (status);
}
