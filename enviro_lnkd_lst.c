#include "shell.h"

/**
 * enviro_lnkd_lst - creates linked list from environmental variables
 * @env: environmental variables
 * Return: linked list
 */
list_t *enviro_lnkd_lst(char **env)
{
	list_t *head;
	int i = 0;

	head = NULL;
	while (env[i] != NULL)
	{
		add_end_node(&head, env[i]);
		i++;
	}
	return (head);
}

/**
 * enviro - print environmental variable
 * @str: user's command into shell
 * @env: environmental variables
 * Return: 0 on success
 */
int enviro(char **str, list_t *env)
{
	_double_pntr(str); /* frees users input */
	prntt_lst(env); /* prints env */
	return (0);
}
