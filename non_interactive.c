#include "shell.h"

/**
 * c_ignore - custom ignores the spaces and newlines
 * @str: envrionmental variables
 * Return: new string
 */
char *c_ignore(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (str);
}

/**
 * no_interakt - handles when user pipes commands into shell via pipeline
 * @env: envrionmental variables
 */
void no_interakt(list_t *env)
{
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command = NULL, *n_command = NULL, **n_line, **token;

	i = gt_lin(&command);
	if (i == 0)
	{
		free(command);
		exit(0);
	}
	n_command = command;
	command = c_ignore(command);
	n_line = str_toknn(command, "\n"); /* tokenize each command of string */
	if (n_command != NULL)
		free(n_command);
	n = 0;
	while (n_line[n] != NULL)
	{
		command_line_no++;
		token = NULL; /* tokenize each command in array of cmd */
		token = str_toknn(n_line[n], " ");
		exit_stat = builtt_into(token, env, command_line_no, n_line);
		if (exit_stat)
		{
			n++;
			continue;
		}
		exit_stat = exec_cmd(token, env, command_line_no);
		n++;
	}
	_double_pntr(n_line);
	_lnkd_lst_fri(env);
	exit(exit_stat);
}
