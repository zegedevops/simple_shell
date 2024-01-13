#include "shell.h"

/**
 * ctrl_c - ignore Ctrl-C input and print prompt again
 * @n: takes in int from the signal
 */
void ctrl_c(int n)
{
	(void)n;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * builtt_into - handle builtins (exit, env, cd)
 * @token: user typed command
 * @env: environmental variable
 * @num: take in nth user command typed to write error message
 * @command: bring in command to free
 * Return: 1 if acted on builtin, 0 if not
 */
int builtt_into(char **token, list_t *env, int num, char **command)
{
	int i = 0;

	/* user types "exit", free cmd tokens, and exit */
	if (str_compr(token[0], "exit") == 0)
	{
		i = exit_out(token, env, num, command);
	}
	/* user types "env", print, free cmd tokens, and reprompt */
	else if (str_compr(token[0], "env") == 0)
	{
		enviro(token, env);
		i = 1;
	}
	/* user types "cd" , it will change directory */
	else if (str_compr(token[0], "cd") == 0)
	{
		i = c_dir(token, env, num);
	}
	/* user types "setenv", create or modify linked list node */
	else if (str_compr(token[0], "setenv") == 0)
	{
		_setenv(&env, token);
		i = 1;
	}
	/* user types "setenv", remove linked list node */
	else if (str_compr(token[0], "unsetenv") == 0)
	{
		_unsetenv(&env, token);
		i = 1;
	}
	return (i);
}

/**
 * ign_space - return string without spaces in front
 * @str: string
 * Return: new string
 */
char *ign_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * ctrl_D - exits program if Ctrl-D was pressed
 * @i: characters read via gt_lin
 * @command: user typed in command
 * @env: environmental variable linked list
 */
void ctrl_D(int i, char *command, list_t *env)
{
	if (i == 0) /* handle Ctrl+D */
	{
		free(command); /* exit with a newline if in shell */
		_lnkd_lst_fri(env);
		if (isatty(STDIN_FILENO))/* ctrl+d print newline */
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * promppt - repeatedly promppts user and executes user's cmds if applicable
 * @en: envrionmental variables
 * Return: 0 on success
 */
int promppt(char **en)
{
	list_t *env;
	size_t i = 0, n = 0;
	int command_line_no = 0, exit_stat = 0;
	char *command, *n_command, **token;

	env = enviro_lnkd_lst(en);
	do {
		command_line_no++;
		if (isatty(STDIN_FILENO)) /* repromppt if in interactive shell */
			write(STDOUT_FILENO, "$ ", 2);
		else
			no_interakt(env);
		signal(SIGINT, ctrl_c); /* makes ctrl+c not to work */
		command = NULL; i = 0; /* reset vars each time the loop runs */
		i = gt_lin(&command); /* read the user cmd in stdin */
		ctrl_D(i, command, env); /* exits the shell if ctrl-D */
		n_command = command;
		command = ign_space(command);
		n = 0;
		while (command[n] != '\n') /* replace gt_lin's \n with \0 */
			n++;
		command[n] = '\0';
		if (command[0] == '\0') /* repromppt if user hits enter only */
		{
			free(n_command); continue;
		}
		token = NULL; token = str_toknn(command, " "); /*token user cmd*/
		if (n_command != NULL)
			free(n_command);
		exit_stat = builtt_into(token, env, command_line_no, NULL);
		if (exit_stat)
			continue;
		exit_stat = exec_cmd(token, env, command_line_no);
	} while (1); /* keep repeating until user exits shell */
	return (exit_stat);
}
