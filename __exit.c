#include "shell.h"

/**
 * c_atoi - cust atoi converting string to int
 * @s: string
 * Return: numb if success, -1 if string of non-numbers
 */
int c_atoi(char *s)
{
	int i = 0;
	unsigned int num = 0;

	while (s[i] != '\0')
	{
		if (s[i] >= '0' && s[i] <= '9') /* calculate numbers */
			num = num * 10 + (s[i] - '0');
		if (s[i] > '9' || s[i] < '0') /* acct for non-numb */
			return (-1);
		i++;
	}
	return (num);
}

/**
 * exit_out - frees user input and exits main program with a value
 * @str: user command to shell
 * @env: bring environmental variable that free at error
 * @num: bring in nth user command line input and print in error message
 * @command: bring in cmd to free
 * Return: 0 if success 2 if fail
 */
int exit_out(char **str, list_t *env, int num, char **command)
{
	int e_value = 0;

	if (str[1] != NULL) /* no val given after exit, return 0 */
		e_value = c_atoi(str[1]);

	if (e_value == -1) /* val given after exit is not valid, perror */
	{
		wrong_num(str[1], num, env); /* print error message */
		_double_pntr(str);
		return (2);
	}
	_double_pntr(str); /* free user input before exiting program */
	_lnkd_lst_fri(env);
	if (command != NULL)
		_double_pntr(command);
	exit(e_value);
}
