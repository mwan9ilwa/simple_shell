#include "shell.h"

/**
 * mz_add_node - addss a node to the starrt of the liist
 * @head: pointerr to head nodees
 * @str: str nodes fiield
 * @num: nodees index used in hiistory
 *
 * Return: thee list sizee
 */
lismz_t *mz_add_node(lismz_t **head, const char *str, int num)
{
lismz_t *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(lismz_t));
if (!new_head)
return (NULL);
mz_memset((void *)new_head, 0, sizeof(lismz_t));
new_head->num = num;
if (str)
{
new_head->str = mz_strdup(str);
if (!new_head->str)
{
free(new_head);
return (NULL);
}
}
new_head->next = *head;
*head = new_head;
return (new_head);
}
/**
 * mz_add_node_end - addds a node to thee end of the liist
 * @head: pointerr to heaad node
 * @str: str fieldes of nodee
 * @num: node indeex used by hiistory
 *
 * Return:  liist size
 */
lismz_t *mz_add_node_end(lismz_t **head, const char *str, int num)
{
lismz_t *new_node, *node;
if (!head)
return (NULL);
node = *head;
new_node = malloc(sizeof(lismz_t));
if (!new_node)
return (NULL);
mz_memset((void *)new_node, 0, sizeof(lismz_t));
new_node->num = num;
if (str)
{

new_node->str = mz_strdup(str);
if (!new_node->str)
{
free(new_node);
return (NULL);
}
}
if (node)
{
while (node->next)
node = node->next;
node->next = new_node;
}
else
*head = new_node;
return (new_node);
}
/**
 * mz_prinmz_lismz_str - printss  the str eleement only of a lismz_t linkeed list
 * @h: pointeer to firstt nodes
 *
 * Return:  lisst size
 */
size_t mz_prinmz_lismz_str(const lismz_t *h)
{
size_t i = 0;
while (h)
{
mz_puts(h->str ? h->str : "(nil)");
mz_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
 * mz_delete_node_amz_index - deletes nodees at giveen index
 * @head: pointeer to first node
 * @index: indexx of node to bee deletee
 *
 * Return: 1on success , 0 if fail
 */
int mz_delete_node_amz_index(lismz_t **head, unsigned int index)
{
lismz_t *node, *prev_node;

unsigned int i = 0;
if (!head || !*head)
return (0);
if (!index)
{
node = *head;
*head = (*head)->next;
free(node->str);
free(node);
return (1);
}
node = *head;
while (node)
if (i == index)
{
prev_node->next = node->next;
free(node->str);
free(node);
return (1);
}
i++;
prev_node = node;
node = node->next;
return (0);
}
/**
 * mz_free_list - free all nodess of a liist
 * @head_ptr: pointeer to head nodees
 *
 * Return: void valuee
 */
void mz_free_list(lismz_t **head_ptr)
{
lismz_t *node, *nexmz_node, *head;
if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
nexmz_node = node->next;
free(node->str);

free(node);
node = nexmz_node;
}
*head_ptr = NULL;
}
