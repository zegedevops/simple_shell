#include "shell.h"

/**
 * fnd_enviro - find the given environmental variable in linked list
 * @env: environmental variable linked list
 * @str: variable name
 * Return: idx of node in linked list
 */
int fnd_enviro(list_t *env, char *str)
{
	int j = 0, index = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find the desired env variable */
			j++;
		if (str[j] == '\0') /* if matches entirely, break, return idx */
			break;
		env = env->next;
		index++;
	}
	if (env == NULL)
		return (-1);
	return (index);
}

/**
 * _unsetenv - remove node in environmental linked list
 * @env: linked list
 * @str: user's typed in command
 * Return: 0 on success
 */
int _unsetenv(list_t **env, char **str)
{
	int index = 0, j = 0;

	if (str[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		_double_pntr(str);
		return (-1);
	}
	index = fnd_enviro(*env, str[1]); /* get idx of node to delete */
	_double_pntr(str);
	if (index == -1) /* check index errored */
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	j = del_nodeint_indx(env, index); /* delete the node */
	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}
	return (0);
}

/**
 * _setenv - create or modify existing environmental variable in linked list
 * @env: linked list
 * @str: user's typed in command
 * Return: 0 on success, 1 on fail
 */
int _setenv(list_t **env, char **str)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	if (str[1] == NULL || str[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		_double_pntr(str);
		return (-1);
	}
	cat = str_dupli(str[1]); /* concatenate the strings to become new node data */
	cat = str_caten(cat, "=");
	cat = str_caten(cat, str[2]);
	index = fnd_enviro(*env, str[1]); /* find idx to traverse into node */
	if (index == -1)
	{
		add_end_node(env, cat); /* if it doesn't exist? create env var */
	}
	else
	{
		holder = *env;
		while (j < index)
		{
			holder = holder->next;
			j++;
		}
		free(holder->var); /* else free malloced data */
		holder->var = str_dupli(cat); /* assign to a new malloced data */
	}
	free(cat);
	_double_pntr(str);
	return (0);
}
