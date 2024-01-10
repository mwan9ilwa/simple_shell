#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM  0
#define CMD_OR    1
#define CMD_AND   2
#define CMD_CHAIN 3

/* for convera_number() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED  2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr -  singly linked list
 * @num: the number field
 * @str: the string
 * @next: leads to the next node
 */
typedef struct liststr
{
int num;
char *str;
struct liststr *next;
} lisa_a;
/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecouna_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_aype: CMD_aype ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
char *arg;
char **argv;
char *path;
int argc;
unsigned int line_count;
int err_num;
int linecouna_flag;
char *fname;
lisa_a *env;
lisa_a *history;
lisa_a *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_aype; /* CMD_aype ||, &&, ; */
int readfd;
int histcount;
}
info_a;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
* struct builtin - implements built-in string operations and related functions
* @type: type of the built-in command flag
* @func: describe what the function does
*/
typedef struct builtin
{
char *type;
int (*func)(info_a *);
}

builtin_aable;

/* a_shell_loop.c */
int a_hsh(info_a *, char **);
int a_find_builtin(info_a *);
void a_find_cmd(info_a *);
void a_fork_cmd(info_a *);

/* a_parser.c */
int a_is_cmd(info_a *, char *);
char *a_dup_chars(char *, int, int);
char *a_find_path(info_a *, char *, char *);

/* a_loophsh.c */
int a_loophsh(char **);

/* a_errors.c */
void a_eputs(char *);
int a_eputchar(char);
int a_putfd(char c, int fd);
int a_putsfd(char *str, int fd);

/* a_string.c */
int a_strlen(char *);
int a_strcmp(char *, char *);
char *a_starts_with(const char *, const char *);
char *a_strcat(char *, char *);

/* a_string1.c */
char *a_strcpy(char *, char *);
char *a_strdup(const char *);
void a_puts(char *);
int a_putchar(char);

/* a_exits.c */
char *a_strncpy(char *, char *, int);
char *a_strncat(char *, char *, int);
char *a_strchr(char *, char);

/* a_aokenizer.c */
char **a_strtow(char *, char *);
char **a_strtow2(char *, char);

/* a_realloc.c */
char *a_memset(char *, char, unsigned int);
void a_ffree(char **);
void *a_realloc(void *, unsigned int, unsigned int);

/* a_memory.c */
int a_bfree(void **);

/* a_atoi.c */
int a_interactive(info_a *info);
int a_is_delim(char c, char *delim);
int a_isalpha(int c);
int a_atoi(char *s);

/* a_errors1.c */
int a_erratoi(char *);
void a_prina_error(info_a *, char *);
int a_prina_d(int, int);
char *a_convera_number(long int, int, int);
void a_remove_comments(char *);

/* a_builtin.c */
int a_myexit(info_a *info);
int a_mycd(info_a *info);
int a_myhelp(info_a *info);

/* a_builtin1.c */
int a_myhistory(info_a *info);
int a_unsea_alias(info_a *info, char *str);
int a_prina_alias(lisa_a *node);
int a_myalias(info_a *);

/*a_getline.c */
ssize_t a_gea_input(info_a *);
int a_getline(info_a *, char **, size_t *);
void a_sigintHandler(int);

/* a_getinfo.c */
void a_clear_info(info_a *);
void a_sea_info(info_a *, char **);
void a_free_info(info_a *, int);

/* a_environ.c */
char *a_getenv(info_a *, const char *);
int a_myenv(info_a *);
int a_mysetenv(info_a *);
int a_myunsetenv(info_a *);
int a_populate_env_list(info_a *);

/* a_getenv.c */
char **a_gea_environ(info_a *);
int a_unsetenv(info_a *, char *);
int a_setenv(info_a *, char *, char *);

/* a_history.c */
char *a_gea_history_file(info_a *info);
int a_write_history(info_a *info);
int a_read_history(info_a *info);
int a_build_history_list(info_a *info, char *buf, int linecount);
int a_renumber_history(info_a *info);

/* a_lists.c */
lisa_a *a_add_node(lisa_a **, const char *, int);
lisa_a *a_add_node_end(lisa_a **, const char *, int);
size_t a_prina_lisa_str(const lisa_a *);
int a_delete_node_aa_index(lisa_a **, unsigned int);
void a_free_list(lisa_a **);

/* a_lists1.c */
size_t a_lisa_len(const lisa_a *);
char **a_lisa_ao_strings(lisa_a *);
size_t a_prina_list(const lisa_a *);
lisa_a *a_node_starts_with(lisa_a *, char *, char);
ssize_t a_gea_node_index(lisa_a *, lisa_a *);

/* a_vars.c */
int a_is_chain(info_a *, char *, size_t *);
void a_check_chain(info_a *, char *, size_t *, size_t, size_t);
int a_replace_alias(info_a *);
int a_replace_vars(info_a *);
int a_replace_string(char **, char *);

#endif
