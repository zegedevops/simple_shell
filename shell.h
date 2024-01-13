#ifndef SHELL
#define SHELL

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <signal.h>

/**
 * struct list - link list for environ variables
 * @var: hold environ variable strng
 * @next: point to subsequent node
 */
typedef struct list
{
	char *var;
	struct list *next;

} list_t;

/* funct prototypes */
int promppt(char **env);
void *re_alloc(void *ptr, unsigned int old_size, unsigned int new_size);
size_t gt_lin(char **str);
int t_strlen(char *str, int pos, char delm);
char *ign_space(char *str);
char **str_toknn(char *str, char *delm);
char **c_strn_toknn(char *str, char *delm);
char *str_caten(char *dest, char *src);
char *str_dupli(char *str);
char *str_copi(char *dest, char *src);
int str_compr(char *s1, char *s2);
int c_dir(char **str, list_t *env, int num);
int builtt_into(char **token, list_t *env, int num, char **command);
void no_interakt(list_t *env);
char *which_path(char *str, list_t *env);
int exit_out(char **s, list_t *env, int num, char **command);
int exec_cmd(char *argv[], list_t *env, int num);
void _double_pntr(char **str);
void _lnkd_lst_fri(list_t *list);
int enviro(char **str, list_t *env);
char *gt_enviro(char *str, list_t *env);
list_t *enviro_lnkd_lst(char **env);
list_t *add_end_node(list_t **head, char *str);
size_t prntt_lst(list_t *h);
int del_nodeint_indx(list_t **head, int index);
int _unsetenv(list_t **env, char **str);
int _setenv(list_t **env, char **str);
int fnd_enviro(list_t *env, char *str);
void nt_seen(char *str, int num, list_t *env);
void cnt_cdir_too(char *str, int c_n, list_t *env);
void wrong_num(char *str, int c_n, list_t *env);
char *intgr_into_strng(int number);

#endif
