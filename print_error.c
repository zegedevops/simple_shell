#include "shell.h"

/**
 * nt_seen - write an error ("sh: 1: lss: not found")
 * @str: user typed command
 * @c_n: nth user typed command
 * @env: bring in environmental variables linked list to write the shell name
 */
void nt_seen(char *str, int c_n, list_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = gt_enviro("_", env); /* get shell name and write */
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = intgr_into_strng(c_n); /* convert cmd line number to string and write */
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	count = 0;
	while (str[count] != '\0')
		count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found\n", 10);
}

/**
 * cnt_cdir_too - write the error ("sh: 2: cd: can't cd to xyz")
 * @str: user's typed argument after the cmd cd
 * @c_n: nth user typed command
 * @env: bring in environmental variables linked list to write shell name
 */
void cnt_cdir_too(char *str, int c_n, list_t *env)
{
	int count = 0;
	char *shell, *num;

	shell = gt_enviro("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = intgr_into_strng(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	count = 0;
	while (str[count] != '\0')
		count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * wrong_num - write error ("sh: 3: exit: Illegal number abc (or -1)")
 * @str: user typed argument after the cmd exit
 * @c_n: nth user typed command
 * @env: bring in environmental variables linked list and write shell name
 */
void wrong_num(char *str, int c_n, list_t *env)
{
	int count = 0;
	char *shell = NULL, *num = NULL;

	shell = gt_enviro("_", env);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = intgr_into_strng(c_n);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "exit: Illegal number: ", 22);
	count = 0;
	while (str[count] != '\0')
		count++;
	write(STDOUT_FILENO, str, count);
	write(STDOUT_FILENO, "\n", 1);
}
