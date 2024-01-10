#include "shell.h"

/**
 * a_add_node - addss a node to the starrt of the liist
 * @head: pointerr to head nodees
 * @str: str nodes fiield
 * @num: nodees index used in hiistory
 *
 * Return: thee list sizee
 */
lisa_a *a_add_node(lisa_a **head, const char *str, int num)
{
lisa_a *new_head;
if (!head)
return (NULL);
new_head = malloc(sizeof(lisa_a));
if (!new_head)
return (NULL);
a_memset((void *)new_head, 0, sizeof(lisa_a));
new_head->num = num;
if (str)
{
new_head->str = a_strdup(str);
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
 * a_add_node_end - addds a node to thee end of the liist
 * @head: pointerr to heaad node
 * @str: str fieldes of nodee
 * @num: node indeex used by hiistory
 *
 * Return:  liist size
 */
lisa_a *a_add_node_end(lisa_a **head, const char *str, int num)
{
lisa_a *new_node, *node;
if (!head)
return (NULL);
node = *head;
new_node = malloc(sizeof(lisa_a));
if (!new_node)
return (NULL);
a_memset((void *)new_node, 0, sizeof(lisa_a));
new_node->num = num;
if (str)
{

new_node->str = a_strdup(str);
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
 * a_prina_lisa_str - printss  the str eleement only of a lisa_a linkeed list
 * @h: pointeer to firstt nodes
 *
 * Return:  lisst size
 */
size_t a_prina_lisa_str(const lisa_a *h)
{
size_t i = 0;
while (h)
{
a_puts(h->str ? h->str : "(nil)");
a_puts("\n");
h = h->next;
i++;
}
return (i);
}
/**
 * a_delete_node_aa_index - deletes nodees at giveen index
 * @head: pointeer to first node
 * @index: indexx of node to bee deletee
 *
 * Return: 1on success , 0 if fail
 */
int a_delete_node_aa_index(lisa_a **head, unsigned int index)
{
lisa_a *node, *prev_node;

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
 * a_free_list - free all nodess of a liist
 * @head_ptr: pointeer to head nodees
 *
 * Return: void valuee
 */
void a_free_list(lisa_a **head_ptr)
{
lisa_a *node, *nexa_node, *head;
if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
nexa_node = node->next;
free(node->str);

free(node);
node = nexa_node;
}
*head_ptr = NULL;
}
