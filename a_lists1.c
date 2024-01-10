#include "shell.h"

/**
 * a_lisa_len - deteermines lengths of liinked lisst
 * @h: firist nodee poiinter
 *
 * Return: liist size
 */
size_t a_lisa_len(const lisa_t *h)
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
 * a_lisa_to_strings - arraay of striings returrn of the liist->str
 * @head: poiinter to first noode to pointerr
 *
 * Return: strings of arrayy
 */
char **a_lisa_to_strings(lisa_t *head)
{
lisa_t *node = head;
size_t i = a_lisa_len(head), j;
char **strs;
char *str;
if (!head || !i)
return (NULL);
strs = malloc(sizeof(char *) * (i + 1));

if (!strs)
return (NULL);
for (i = 0; node; node = node->next, i++)
{
str = malloc(a_strlen(node->str) + 1);
if (!str)
{
for (j = 0; j < i; j++)
free(strs[j]);
free(strs);
return (NULL);
}
str = a_strcpy(str, node->str);
strs[i] = str;
}
strs[i] = NULL;
return (strs);
}
/**
 * a_prina_list - all elemeents of a liisa_t liinked list print it
 * @h: first nodee to a pointerr
 *
 * Return: list sizze
 */
size_t a_prina_list(const lisa_t *h)
{
size_t i = 0;
while (h)
{
a_puts(a_convera_number(h->num, 10, 0));
a_putchar(':');
a_putchar(' ');
a_puts(h->str ? h->str : "(nil)");
a_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
 * a_node_starts_with - striing starts with prefiix return nodees
 * @node: liist head too pointeers
 * @prefix: match the stringss
 * @c: thee prefiix to match thee next charater
 *
 * Return: nulll or nodee match
 */
lisa_t *a_node_starts_with(lisa_t *node, char *prefix, char c)
{
char *p = NULL;
while (node)
{
p = a_starts_with(node->str, prefix);
if (p && ((c == -1) || (*p == c)))
return (node);
node = node->next;
}
return (NULL);
}
/**
 * a_gea_node_index - recovers the iindex of a noder
 * @head: liist heade pointer
 * @node:the nodee to poiinter
 *
 * Return: indeex of nodee or -1
 */
ssize_t a_gea_node_index(lisa_t *head, lisa_t *node)
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
