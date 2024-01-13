#include "shell.h"

/**
 * gt_lin - stores in malloced buffer in user command in shell
 * @str: buffer
 * Return: numb of character read
 */
size_t gt_lin(char **str)
{
	ssize_t i = 0, size = 0, t = 0, t2 = 0, n = 0;
	char buff[1024];

	/* read while there is stdin greater than buffsize; -1 to add a '\0' */
	while (t2 == 0 && (i = read(STDIN_FILENO, buff, 1024 - 1)))
	{
		if (i == -1) /* check if read had error */
			return (-1);

		buff[i] = '\0'; /* terminate buff with \0 use with str_caten */

		n = 0; /* last loop if \n is found in stdin read */
		while (buff[n] != '\0')
		{
			if (buff[n] == '\n')
				t2 = 1;
			n++;
		}

		/* copy what read to buff into gt_lin's buffer */
		if (t == 0) /* malloc first time */
		{
			i++;
			*str = malloc(sizeof(char) * i);
			*str = str_copi(*str, buff);
			size = i;
			t = 1;
		}
		else /* re_alloc via str_caten with each loop */
		{
			size += i;
			*str = str_caten(*str, buff);
		}
	}
	return (size);
}
