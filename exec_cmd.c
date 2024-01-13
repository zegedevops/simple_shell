#include "shell.h"

/**
 * c_exit - free user typed command and also linked list then exit
 * @str: user typed cmd
 * @env: input linked list of envirnment
 */
void c_exit(char **str, list_t *env)
{
	_double_pntr(str);
	_lnkd_lst_fri(env);
	_exit(0);
}

/**
 * exec_cmd - exec cmd user typed in shell
 * @s: cmd typed
 * @env: environmental variable
 * @num: nth users command; used in error mssg
 * Return: 0 on success
 */
int exec_cmd(char **s, list_t *env, int num)
{
	char *holder;
	int status = 0, t = 0;
	pid_t pid;

	/* check command is absolute path */
	if (access(s[0], F_OK) == 0)
	{
		holder = s[0];
		t = 1;
	}
	/* else take out full path */
	else
		holder = which_path(s[0], env);
	/* if not an executable, free */
	if (access(holder, X_OK) != 0)
	{
		nt_seen(s[0], num, env);
		_double_pntr(s);
		return (127);
	}
	else /* else fork then execute executable command */
	{
		pid = fork();
		if (pid == 0) /* if child process, then execute */
		{
			if (execve(holder, s, NULL) == -1)
			{
				nt_seen(s[0], num, env); /* special error message */
				c_exit(s, env);
			}
		}
		else /* if parent, wait child and free all */
		{
			wait(&status);
			_double_pntr(s);
			if (t == 0)
				free(holder);
		}
	}
	return (0);
}
