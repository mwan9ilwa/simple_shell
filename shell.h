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

/* for convermz_number() */
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
} lismz_t;
/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecounmz_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
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
int linecounmz_flag;
char *fname;
lismz_t *env;
lismz_t *history;
lismz_t *alias;
char **environ;
int env_changed;
int status;

char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
int cmd_buf_type; /* CMD_type ||, &&, ; */
int readfd;
int histcount;
}
info_t;
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
int (*func)(info_t *);
}

builtin_table;

/* mz_shell_loop.c */
int mz_hsh(info_t *, char **);
int mz_find_builtin(info_t *);
void mz_find_cmd(info_t *);
void mz_fork_cmd(info_t *);

/* mz_parser.c */
int mz_is_cmd(info_t *, char *);
char *mz_dup_chars(char *, int, int);
char *mz_find_path(info_t *, char *, char *);

/* mz_loophsh.c */
int mz_loophsh(char **);

/* mz_errors.c */
void mz_eputs(char *);
int mz_eputchar(char);
int mz_putfd(char c, int fd);
int mz_putsfd(char *str, int fd);

/* mz_string.c */
int mz_strlen(char *);
int mz_strcmp(char *, char *);
char *mz_starts_with(const char *, const char *);
char *mz_strcat(char *, char *);

/* mz_string1.c */
char *mz_strcpy(char *, char *);
char *mz_strdup(const char *);
void mz_puts(char *);
int mz_putchar(char);

/* mz_exits.c */
char *mz_strncpy(char *, char *, int);
char *mz_strncat(char *, char *, int);
char *mz_strchr(char *, char);

/* mz_tokenizer.c */
char **mz_strtow(char *, char *);
char **mz_strtow2(char *, char);

/* mz_realloc.c */
char *mz_memset(char *, char, unsigned int);
void mz_ffree(char **);
void *mz_realloc(void *, unsigned int, unsigned int);

/* mz_memory.c */
int mz_bfree(void **);

/* mz_atoi.c */
int mz_interactive(info_t *info);
int mz_is_delim(char c, char *delim);
int mz_isalpha(int c);
int mz_atoi(char *s);

/* mz_errors1.c */
int mz_erratoi(char *);
void mz_prinmz_error(info_t *, char *);
int mz_prinmz_d(int, int);
char *mz_convermz_number(long int, int, int);
void mz_remove_comments(char *);

/* mz_builtin.c */
int mz_myexit(info_t *info);
int mz_mycd(info_t *info);
int mz_myhelp(info_t *info);

/* mz_builtin1.c */
int mz_myhistory(info_t *info);
int mz_unsemz_alias(info_t *info, char *str);
int mz_prinmz_alias(lismz_t *node);
int mz_myalias(info_t *);

/*mz_getline.c */
ssize_t mz_gemz_input(info_t *);
int mz_getline(info_t *, char **, size_t *);
void mz_sigintHandler(int);

/* mz_getinfo.c */
void mz_clear_info(info_t *);
void mz_semz_info(info_t *, char **);
void mz_free_info(info_t *, int);

/* mz_environ.c */
char *mz_getenv(info_t *, const char *);
int mz_myenv(info_t *);
int mz_mysetenv(info_t *);
int mz_myunsetenv(info_t *);
int mz_populate_env_list(info_t *);

/* mz_getenv.c */
char **mz_gemz_environ(info_t *);
int mz_unsetenv(info_t *, char *);
int mz_setenv(info_t *, char *, char *);

/* mz_history.c */
char *mz_gemz_history_file(info_t *info);
int mz_write_history(info_t *info);
int mz_read_history(info_t *info);
int mz_build_history_list(info_t *info, char *buf, int linecount);
int mz_renumber_history(info_t *info);

/* mz_lists.c */
lismz_t *mz_add_node(lismz_t **, const char *, int);
lismz_t *mz_add_node_end(lismz_t **, const char *, int);
size_t mz_prinmz_lismz_str(const lismz_t *);
int mz_delete_node_amz_index(lismz_t **, unsigned int);
void mz_free_list(lismz_t **);

/* mz_lists1.c */
size_t mz_lismz_len(const lismz_t *);
char **mz_lismz_to_strings(lismz_t *);
size_t mz_prinmz_list(const lismz_t *);
lismz_t *mz_node_starts_with(lismz_t *, char *, char);
ssize_t mz_gemz_node_index(lismz_t *, lismz_t *);

/* mz_vars.c */
int mz_is_chain(info_t *, char *, size_t *);
void mz_check_chain(info_t *, char *, size_t *, size_t, size_t);
int mz_replace_alias(info_t *);
int mz_replace_vars(info_t *);
int mz_replace_string(char **, char *);

#endif