#include "shell.h"

/**
 * str_copi - copies string pointed to from src,
 * include the terminating null byte (\0),
 * to the buffer pointed to by dest
 * @dest: copy source to this buffer
 * @src: the source to copy
 * Return: copy of original source
 */

char *str_copi(char *dest, char *src)
{
	int i, len;

	for (len = 0; src[len] != '\0'; len++)
		;

	for (i = 0; i <= len; i++)
		dest[i] = src[i];

	return (dest);
}
