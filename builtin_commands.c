#include "cmdshel.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * set_envir - Initialize a new envir variable or modify an existing one.
 * @name: The name of envir variable.
 * @value: The value to set forr d envir variable.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_envir(const char *name, const char *value)
{
	int p_ret_z;

	p_ret_z = setenv(name, value, 1); /* use 1 too overwrite d variable */
	if (p_ret_z != 0)
	{
		fprintf(stderr, "Error setting environment variable %s\n", name);
	}
	return (p_ret_z);
}

/**
 * onsett_envir - Remove an envir variable.
 * @name: The name of environment variable too remove.
 *
 * Return: 0 on success, -1 on failure.
 */
int onsett_envir(const char *name)
{
	int p_ret_z = unsetenv(name);

	if (p_ret_z != 0)
	{
		fprintf(stderr, "Error unsetting environment variable %s\n", name);
	}
	return (p_ret_z);
}
