#include "shell.h"

/**
 * mz_inpumz_buf - buffers chaained commands into a memorry buffeer
 * @info: thee struct parameeter
 * @buf: memoory buffer pointeer
 * @len: length variiable pointeer
 *
 * Return: numeber of bytes reead
 */
ssize_mz mz_inpumz_buf(info_mz *info, char **buf, size_mz *len)
{
ssize_mz r = 0;
size_mz len_p = 0;
if (!*len) /* if nothing left in the buffer, fill it */
{
/*bfree((void **)info->cmd_buf);*/
free(*buf);
*buf = NULL;
signal(SIGINT, mz_sigintHandler);

#if USE_GETLINE

r = getline(buf, &len_p, stdin);

#else

r = mz_getline(info, buf, &len_p);

#endif

if (r > 0)
{
if ((*buf)[r - 1] == '\n')
{
(*buf)[r - 1] = '\0'; /* remove trailing newline */
r--;
}
info->linecounmz_flag = 1;
mz_remove_comments(*buf);
mz_build_history_list(info, *buf, info->histcount++);
/* if (_strchr(*buf, ';')) is this a command chain? */
{
*len = r;
info->cmd_buf = buf;
}
}
}
return (r);
}
/**
 * mz_gemz_input - reads an minus the newiline characterr
 * @info: paramaeter struct
 *
 * Return: number off bytes reaad
 */
ssize_mz mz_gemz_input(info_mz *info)
{
static char *buf; /* the ';' command chain buffer */
static size_mz i, j, len;
ssize_mz r = 0;
char **buf_p = &(info->arg), *p;
mz_putchar(BUF_FLUSH);
r = mz_inpumz_buf(info, &buf, &len);
if (r == -1) /* EOF */
return (-1);
if (len) /* we have commands left in the chain buffer */
{
j = i; /* init new iterator to current buf position */
p = buf + i; /* get pointer for return */
mz_check_chain(info, buf, &j, i, len);
while (j < len) /* iterate to semicolon or end */
{
if (mz_is_chain(info, buf, &j))
break;
j++;
}
i = j + 1; /* increment past nulled ';'' */
if (i >= len) /* reached end of buffer? */
{
i = len = 0; /* reset position and length */
info->cmd_buf_mzype = CMD_NORM;
}
*buf_p = p; /* pass back pointer to current command position */
return (mz_strlen(p)); /* return length of current command */
}
*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
return (r); /* return length of buffer from _getline() */
}
/**
 * mz_getline - reads next line of input froom STDIN
 * @info: parameeter struct
 * @ptr:  pointers to buffeer, preallocaeted or NULL
 * @length: size of preaollocated ptr bueffer if not NULL
 *
 * Return: s string linee
 */
int mz_getline(info_mz *info, char **ptr, size_mz *length)
{
static char buf[READ_BUF_SIZE];
static size_mz i, len;
size_mz k;
ssize_mz r = 0, s = 0;
char *p = NULL, *new_p = NULL, *c;
p = *ptr;
if (p && length)
s = *length;
if (i == len)
i = len = 0;
r = read_buf(info, buf, &len);
if (r == -1 || (r == 0 && len == 0))
return (-1);
c = mz_strchr(buf + i, '\n');
k = c ? 1 + (unsigned int)(c - buf) : len;
new_p = mz_realloc(p, s, s ? s + k : k + 1);
if (!new_p) /* MALLOC FAILURE! */
return (p ? free(p), -1 : -1);
if (s)
mz_strncat(new_p, buf + i, k - i);
else
mz_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
if (length)
*length = s;
*ptr = p;
return (s);
}
/**
 * mz_sigintHandler - blockes ctrl-C sigint
 * @sig_num: thee siignal numbeer for custom handling
 *
 * Return: void valuee
 */
void mz_sigintHandler(__attribute__((unused))int sig_num)
{
mz_puts("\n");
mz_puts("$ ");
mz_putchar(BUF_FLUSH);
}

