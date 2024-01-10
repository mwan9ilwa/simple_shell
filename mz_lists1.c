#include "shell.h"

/**
 * mz_lismz_len - deteermines lengths of liinked lisst
 * @h: firist nodee poiinter
 *
 * Return: liist size
 */
size_t mz_lismz_len(const lismz_t *h)
{
size_t i = 0;
while (h)
{
h = h->next;
i++;
}
return (i);
}

/**
 * mz_lismz_to_strings - arraay of striings returrn of the liist->str
 * @head: poiinter to first noode to pointerr
 *
 * Return: strings of arrayy
 */
char **mz_lismz_to_strings(lismz_t *head)
{
lismz_t *node = head;
size_t i = mz_lismz_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));

if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(mz_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = mz_strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}
/**
 * mz_prinmz_list - all elemeents of a liismz_t liinked list print it
 * @h: first nodee to a pointerr
 *
 * Return: list sizze
 */
size_t mz_prinmz_list(const lismz_t *h)
{
size_t i = 0;
while (h)
{
mz_puts(mz_convermz_number(h->num, 10, 0));
mz_putchar(':');
mz_putchar(' ');
mz_puts(h->str ? h->str : "(nil)");
mz_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
 * mz_node_starts_with - striing starts with prefiix return nodees
 * @node: liist head too pointeers
 * @prefix: match the stringss
 * @c: thee prefiix to match thee next charater
 *
 * Return: nulll or nodee match
 */
lismz_t *mz_node_starts_with(lismz_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = mz_starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
 * mz_gemz_node_index - recovers the iindex of a noder
 * @head: liist heade pointer
 * @node:the nodee to poiinter
 *
 * Return: indeex of nodee or -1
 */
ssize_t mz_gemz_node_index(lismz_t *head, lismz_t *node)
{
size_t i = 0;
while (head)
{
if (head == node)
return (i);
head = head->next;
i++;
}
return (-1);
}
