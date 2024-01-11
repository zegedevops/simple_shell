#ifndef SHELL_H
#define SHELL_H

#include <stdbool.h>

void cmd_builting_shell(char **args);
void exec_multi_commd(char *cmd, int *x_shel);
int execute_lg_operat(const char *sub_cmd, bool *x_shel);
char **splt_commd_log_opratoz(const char *cmd, bool *x_shel);
char *gt_pat(const char *cmd);
void exec_shel_comnd(char **args, int *x_shel);
char *mi_get_lin(void);
char **cust_token(char *cmd);
int set_envir(const char *name, const char *value);
int onsett_envir(const char *name);
#endif /* SHELL_H */
