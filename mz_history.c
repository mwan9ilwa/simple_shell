#include "shell.h"

/**
 * mz_gemz_history_file -  the hiistory file
 * @info: parameteer struct
 *
 * Return: allocatee strings containg history fiile
 */

char *mz_gemz_history_file(info_mz *info)
{
char *buf, *dir;
dir = mz_getenv(info, "HOME=");
if (!dir)
return (NULL);

buf = malloc(sizeof(char) * (mz_strlen(dir) + mz_strlen(HIST_FILE) + 2));
if (!buf)
return (NULL);
buf[0] = 0;
mz_strcpy(buf, dir);
mz_strcat(buf, "/");
mz_strcat(buf, HIST_FILE);
return (buf);
}
/**
 * mz_write_history - creates a file and appeends to an existiing files
 * @info: the parameeter structs
 *
 * Return: 1 on succeses, elsee -1
 */
int mz_write_history(info_mz *info)
{
ssize_mz fd;
char *filename = mz_gemz_history_file(info);
lismz_mz *node = NULL;
if (!filename)
return (-1);
fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
mz_putsfd(node->str, fd);
mz_putfd('\n', fd);
}
mz_putfd(BUF_FLUSH, fd);
close(fd);
return (1);
}
/**
 * mz_read_history - reaads historry from filee
 * @info: the parameteer structs
 *
 * Return: histcouunt on succeess, 0 otherwise
 */
int mz_read_history(info_mz *info)
{
int i, last = 0, linecount = 0;

ssize_mz fd, rdlen, fsize = 0;
struct stat st;
char *buf = NULL, *filename = mz_gemz_history_file(info);
if (!filename)
return (0);
fd = open(filename, O_RDONLY);
free(filename);
if (fd == -1)
return (0);
if (!fstat(fd, &st))
fsize = st.smz_size;
if (fsize < 2)
return (0);
buf = malloc(sizeof(char) * (fsize + 1));
if (!buf)
return (0);
rdlen = read(fd, buf, fsize);
buf[fsize] = 0;
if (rdlen <= 0)
return (free(buf), 0);
close(fd);
for (i = 0; i < fsize; i++)
if (buf[i] == '\n')
{
buf[i] = 0;
mz_build_history_list(info, buf + last, linecount++);
last = i + 1;
}
if (last != i)
mz_build_history_list(info, buf + last, linecount++);
free(buf);
info->histcount = linecount;
while (info->histcount-- >= HIST_MAX)
mz_delete_node_amz_index(&(info->history), 0);
mz_renumber_history(info);
return (info->histcount);
}
/**
 * mz_build_history_list - entrry to a hiistory linked list addeed
 * @info: structure  araguments for prototypee
 * @buf: buffer struc
 * @linecount: thee historry linecount, histcouunt
 *
 * Return: 0 Always
 */
int mz_build_history_list(info_mz *info, char *buf, int linecount)
{
lismz_mz *node = NULL;
if (info->history)
node = info->history;
mz_add_node_end(&node, buf, linecount);
if (!info->history)
info->history = node;
return (0);
}
/**
 * mz_renumber_history - renumbeers the history linked list afteer changees
 * @info: Struacture conotaining potential araguments. Used to maintain
 *
 * Return: the neew histcounnt
 */
int mz_renumber_history(info_mz *info)
{
lismz_mz *node = info->history;
int i = 0;
while (node)
{
node->num = i++;
node = node->next;
}
return (info->histcount = i);
}
