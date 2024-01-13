#include "shell.h"

/**
 * str_caten - concatenating two strings
 * @dest: string appended to
 * @src: string appended
 * Return: concatenated string
 */
char *str_caten(char *dest, char *src)
{
	int len = 0;
	int len2 = 0;
	int total_len = 0;
	int j = 0;

	/* find the total length of both strings to re_alloc */
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

	while (src[j] != '\0')
	{
		dest[len] = src[j];
		len++;
		j++;
	}
	dest[len] = '\0';

	return (dest);
}
