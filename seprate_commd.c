#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "cmdshel.h"

#define MAX_SUB_COMMANDS 100

/**
 * splt_commd_log_opratoz - Splits the input command into sub-commands
 *                                      based on logical operators
 * @cmd: input command to split
 *
 * Return: array of strings represent d sub-commands
 */

char **splt_commd_log_opratoz(const char *cmd, bool *x_shel)
{
	char *zubb_cmmd_kopi;
	char **zub_commd;
	int sub_cmd_index = 0;
	bool in_quotes = false;
	bool escape = false;
	int r;
	char current_char;
	int cmd_index = 0;

	zubb_cmmd_kopi = strdup(cmd);
	if (zubb_cmmd_kopi == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}

	zub_commd = (char **)malloc(sizeof(char *) * MAX_SUB_COMMANDS);
	if (zub_commd == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/* initialize the first sub-command */
	zub_commd[sub_cmd_index] = (char *)malloc(strlen(cmd) + 1);
	if (zub_commd[sub_cmd_index] == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	/* Loop through each char in input commd */
	for (r = 0; zubb_cmmd_kopi[r] != '\0'; r++)
	{
		current_char = zubb_cmmd_kopi[r];
		if (current_char == '\\')
		{
			/* handle esc charactr */
			escape = !escape;
			if (escape)
			{
				continue;
			}
		}
		else if (current_char == '\'' || current_char == '\"')
		{
			if (!escape)
			{
				in_quotes = !in_quotes;
			}
		}
if (!in_quotes && (current_char == '&' || current_char == '|'))
        {
            if (!escape)
            {
                /* Null-terminate d prev sub-command */
                zub_commd[sub_cmd_index][cmd_index] = '\0';

                /* Move to the next sub-command */
                sub_cmd_index++;

                /* Reset d command indx for d new sub-command */
                cmd_index = 0;

                /* start d new sub-command */
                zub_commd[sub_cmd_index] = (char *)malloc(strlen(cmd) + 1);
                if (zub_commd[sub_cmd_index] == NULL)
                {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
            }
        }
        else
        {
            /* Add d characta too d sub-command */
            zub_commd[sub_cmd_index][cmd_index++] = current_char;
        }

        /* Reset esc flag afta handln d characta */
        escape = false;
    }

    /* Null-terminate d last sub-command */
    zub_commd[sub_cmd_index][cmd_index] = '\0';

    /* kall execute_lg_operat too handle log operators for d sub-command */
    for (r = 0; r <= sub_cmd_index; r++)
    {
        execute_lg_operat(zub_commd[r], x_shel);
    }

    /* Adding a NULL pointr at d end of d sub-commands array too indicate d end */
    zub_commd[sub_cmd_index + 1] = NULL;

    free(zubb_cmmd_kopi);
    return zub_commd;
}
