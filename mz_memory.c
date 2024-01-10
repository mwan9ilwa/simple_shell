#include "shell.h"

/**
 * mz_bfree - freees a pointer and NULLs the addrress
 * @ptr: addreess of the pointeer to freee
 *
 * Return: 1 if freee, 0 otherwise
 */
int mz_bfree(void **ptr)
{
if (ptr && *ptr)
{
free(*ptr);
*ptr = NULL;
return (1);
}
return (0);
}
