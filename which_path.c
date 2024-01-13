#include "shell.h"

/**
 * which_path - brings out cmd by appending it to a matching PATH directory
 * @str: first command user typed in shell
 * @env: environmental variable
 * Return: a copy of fleshed out command
 */
char *which_path(char *str, list_t *env)
{
	char *pth, *cat = NULL, **toks;
	int i = 0;

	/* get and tokenize PATH directories, free original string */
	pth = gt_enviro("PATH", env);
	toks = c_strn_toknn(pth, ":");
	free(pth);

	/* append "/cmd" to each token to see if it's legit */
	i = 0;
	while (toks[i] != NULL)
	{
		if (toks[i][0] == '\0')
			cat = getcwd(cat, 0);
		else
			cat = str_dupli(toks[i]);
		cat = str_caten(cat, "/");
		cat = str_caten(cat, str);
		if (access(cat, F_OK) == 0)
		{
			/* free tokens before returning legit fleshed path */
			_double_pntr(toks);
			return (cat);
		}
		free(cat); /* free concatenated string if cmd is never found */
		i++;
	}
	_double_pntr(toks);
	return (str); /* return string, if not found; won't pass execve */
}
