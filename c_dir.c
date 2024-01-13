#include "shell.h"

/**
 * c_strcat - concatenate different strings, ignor the first character ("~" in cd)
 * @dest: string appended to
 * @src: string appended
 * Return: concatenated string
 */
char *c_strcat(char *dest, char *src)
{
	int len = 0;
	int len2 = 0;
	int total_len = 0;
	int j = 0;

	/* find length of both strings to re_alloc */
	while (dest[len] != '\0')
	{
		len++;
		total_len++;
	}
	while (src[len2] != '\0')
	{
		len2++;
		total_len++;
	}

	/* re_alloc because dest was malloced outside function */
	dest = re_alloc(dest, len, sizeof(char) * total_len + 1);

	j = 1; /* ignore first character */
	while (src[j] != '\0')
	{
		dest[len] = src[j];
		len++;
		j++;
	}
	dest[len] = '\0';

	return (dest);
}

/**
 * c_setenv - custom _setenv concatenating string first then setting
 * @env: environmental variable linked list
 * @name: environmental variable name
 * @dir: directory path
 * Return: 0 on success
 */
int c_setenv(list_t **env, char *name, char *dir)
{
	int index = 0, j = 0;
	char *cat;
	list_t *holder;

	cat = str_dupli(name); /* create duplicate concatenated string */
	cat = str_caten(cat, "=");
	cat = str_caten(cat, dir);
	index = fnd_enviro(*env, name); /* getting idx to env var in linked list */

	/* traverse to idx, free node data, reassign data */
	holder = *env;
	while (j < index)
	{
		holder = holder->next;
		j++;
	}
	free(holder->var);
	holder->var = str_dupli(cat);
	free(cat);
	return (0);
}

/**
 * cd_only - change directory to home
 * @env: bring environmental linked list update PATH nd OLDPWD
 * @current: bring PWD
 */
void cd_only(list_t *env, char *current)
{
	char *home = NULL;

	home = gt_enviro("HOME", env);
	c_setenv(&env, "OLDPWD", current); /* update env OLDPWD */
	free(current);
	if (access(home, F_OK) == 0) /* if exist, go to home dir */
		chdir(home);
	current = NULL;
	current = getcwd(current, 0);
	c_setenv(&env, "PWD", current); /* update env PWD */
	free(current);
	free(home);
}
/**
 * cd_execute - execute cd
 * @env: bring environmental linked list to update PATH and OLDPWD
 * @current: current working directotry
 * @dir: directory path to change to
 * @str: 1st argument to write out error
 * @num: line number to write out error
 * Return: 0 if success 2 if fail
 */
int cd_execute(list_t *env, char *current, char *dir, char *str, int num)
{
	int i = 0;

	if (access(dir, F_OK) == 0)
	{
		c_setenv(&env, "OLDPWD", current); /* updat env OLDPWD */
		free(current);
		chdir(dir);
		current = NULL;
		current = getcwd(current, 0); /* get current working directory */
		c_setenv(&env, "PWD", current); /* update enviro PWD */
		free(current);
	}
	else
	{
		cnt_cdir_too(str, num, env);
		free(current);
		i = 2;
	}
	return (i);
}

/**
 * c_dir - change directory
 * @str: user's type in command
 * @env: enviromental linked list that retrieves HOME and OLDPWD path
 * @num: nth user cmd, used as error message
 * Return: 0 if success 2 if failed
 */
int c_dir(char **str, list_t *env, int num)
{
	char *current = NULL, *dir = NULL;
	int exit_stat = 0;

	current = getcwd(current, 0); /* store pwd */
	if (str[1] != NULL)
	{
		if (str[1][0] == '~') /* Uses: cd ~ */
		{
			dir = gt_enviro("HOME", env);
			dir = c_strcat(dir, str[1]);
		}
		else if (str[1][0] == '-') /* Uses: cd - */
		{
			if (str[1][1] == '\0')
				dir = gt_enviro("OLDPWD", env);
		}
		else /* Use: cd directory1 */
		{
			if (str[1][0] != '/')
			{
				dir = getcwd(dir, 0);
				dir = str_caten(dir, "/");
				dir = str_caten(dir, str[1]);
			}
			else
				dir = str_dupli(str[1]);
		}
		exit_stat = cd_execute(env, current, dir, str[1], num);
		free(dir);
	}
	else
		cd_only(env, current);
	_double_pntr(str); /* free usr input */
	return (exit_stat);
}
