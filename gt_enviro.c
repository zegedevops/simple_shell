#include "shell.h"

/**
 * c_strdup - custom string duplication; exclude starting bytes
 * @str: string to duplicate
 * @cs: number of bytes to exclude
 * Return: string
 */
char *c_strdup(char *str, int cs)
{
	char *duplicate_str;
	int i, len = 0;

	if (str == NULL) /* validate str input */
		return (NULL);

	/* calculate len + null terminator to the malloc */
	while (*(str + len))
		len++;
	len++;

	/* allocate memory, note exclude environmental variable title (PATH) */
	duplicate_str = malloc(sizeof(char) * (len - cs));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (len - cs))
	{
		*(duplicate_str + i) = *(str + cs + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * gt_enviro - finds and returns copy of the requested environmental variable
 * @str: string to store in
 * @env: entire set of environmental variables
 * Return: copy of requested environmental variable
 */
char *gt_enviro(char *str, list_t *env)
{
	int j = 0, cs = 0;

	while (env != NULL)
	{
		j = 0;
		while ((env->var)[j] == str[j]) /* find the desired env variable */
			j++;
		if (str[j] == '\0' && (env->var)[j] == '=')
			break;
		env = env->next;
	}

	while (str[cs] != '\0') /* find how many bytes are in env variable title */
		cs++;
	cs++; /*counts 1 more for = sign*/
	return (c_strdup(env->var, cs)); /* make copy of variable w/o title */
}
