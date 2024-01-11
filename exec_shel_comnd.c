#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "cmdshel.h"
#include <unistd.h>
#include <ctype.h> 

#define MAX_CMD_LEN 1024
#define MAX_ARGS 10
extern char **environ;

char *gt_pat(const char *cmd)
{
	char *path_env_copy = strdup(getenv("PATH")); /* Gett d PATH environment variable */
	char *path_copy = strdup(path_env_copy); 
	char *path = strtok(path_copy, ":"); /* Tokeniz d PATH variable by ':' */
	char *full_path = NULL;
	int lent_of_path;
	char last_char;
	
	if (strcmp(cmd, "exit") == 0)
			{	
				free(full_path);
				return ("builtin");
			}
	if (strcmp(cmd, "getenvir") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	if (strcmp(cmd, "unsetenv") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	if (strcmp(cmd, "cd") == 0)
	{
		free(full_path);
		return ("builtin");
	}
	while (path != NULL)
	{	
		lent_of_path = strlen(path);
		last_char = path[lent_of_path-1];
		full_path = malloc(strlen(path) + strlen(cmd) + 2); /* Allocat mem forr d full path */
		if (full_path == NULL)
		{
			fprintf(stderr, "Memory allocation error\n");
			exit(EXIT_FAILURE);
		}
		if (cmd[0] == '/')
		{
			strcpy(full_path, cmd);
		}
		else if (last_char =='/')
				{
					snprintf(full_path, lent_of_path + strlen(cmd) + 1, "%s%s", path, cmd);
				}
				else
				{
					snprintf(full_path, lent_of_path + strlen(cmd) + 2, "%s/%s", path, cmd);
	       	/* Concat d directory path and d command */
		}
		if (access(full_path, X_OK) == 0) /* Check if the file is executable */
			{
				free(path_env_copy);
				return (full_path);
			}	/* Return the full path if the file is executable */
		free(full_path); /* Free d memory if the file is not exec */
		path = strtok(NULL, ":"); /* Get the next directory in PATH */
	}
	free(path_env_copy);
	free (path_copy);
	free(full_path);
	return NULL; /* Return NULL if the command not found in directory list PATH */
}
/**
 * exec_shel_comnd - Execut  shel command
 * @cmd: The command to exec
 * @x_shel: pointer too d exit shell flag
 */
void exec_shel_comnd(char **args, int *x_shel)
{
    char *path_copy = NULL;
    char **dirs;
    char cmd_path[MAX_CMD_LEN];
    int dir_index = 0;
    char *path;
    int r;
    int exit_status;


    path = gt_pat(args[0]);
    if (path == NULL)
    {
        printf("Error: PATH variable not set\n");
        return;
    }
    if (strcmp(args[0], "exit") == 0)
    {
	    if (args[1] != NULL)
	    {
		    r = 0;
		    while (args[1][r] != '\0')
		    {
			    if (!isdigit(args[1][r]))
			    {
				    fprintf(stderr, "Error: Invalid exit status\n");
				    return;
			    }
			    r++;
		    }
		    exit_status = atoi(args[1]);
		    exit(exit_status);
	    }
	    else
	    {
        	*x_shel = 1; /* Set the exit shell flag */
	    }
	    return;
    }
    else if (strcmp(args[0], "getenvir") == 0)
    {
	    if (args[1] == NULL || args[2] == NULL)
	    {
		    fprintf(stderr, "Usage: getenvir VARIABLE VALUE\n");
		    return;
	    }
	    set_envir(args[1], args[2]);
	    return;
    }
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
			return;
		}
		onsett_envir(args[1]);
		return;
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		/* call cmd_builting_shell funct too handle cd command */
		cmd_builting_shell(args);
		return;
	}
    else if (strcmp(args[0], "env") == 0)
    {
       /*  Print d envir variables */
        char **env = environ;
        while (*env)
        {
            printf("%s\n", *env);
            env++;
        }
    }
    else
    {
        /* Chek whether commd exist in d PATH */
        /* path = gt_pat(args[0]);
        if (path == NULL)
        {
            printf("Error: PATH variable not set\n");
            return;
        } */
        path_copy = strdup(path);
        dirs = cust_token(path_copy);
        while (dirs[dir_index] != NULL)
        {
            snprintf(cmd_path, MAX_CMD_LEN, "%s", dirs[dir_index]);
           /* r = 0;
            while (args[r] != NULL)
            {
                printf("%s ", args[r]);
                r++;
            }
            printf("\n"); */

            if (access(cmd_path, X_OK) == 0)
            {
                /* Exec d command */
                pid_t pid = fork();
                if (pid == -1)
                {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }
                else if (pid == 0)
                {
                    execv(cmd_path, args);
                    perror("execv");
                    exit(EXIT_FAILURE);
                }
                else
                {
                    int status;
                    waitpid(pid, &status, 0);
                    if (WIFEXITED(status))
                    {
                        int exit_status = WEXITSTATUS(status);
                        if (exit_status != 0)
                        {
                            printf("Command '%s' returned non-zero exit status %d\n", args[0], exit_status);
                        }
                    }
                    else if (WIFSIGNALED(status))
                    {
                        int signal_num = WTERMSIG(status);
                        printf("Command '%s' terminated by signal %d\n", args[0], signal_num);
                    }
                    else if (WIFSTOPPED(status))
                    {
                        int signal_num = WSTOPSIG(status);
                        printf("Command '%s' stopped by signal %d\n", args[0], signal_num);
                    } 
			return;
                }
                return;
            }
            dir_index++;
        }
    }
    free(path_copy);
    free(dirs);
    for (r = 0; args[r] != NULL; r++)
    {
	    free(args[r]);
    }
    free(args);
}
