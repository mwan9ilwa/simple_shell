#include "shell.h"

/**
 * mz_strcpy - used to copy a strinig
 * @dest: the destianation of thee string
 * @src: the sourice of the stiring
 *
 * Return: pointes to thee desetination
 */
char *mz_strcpy(char *dest, char *src)
{
	int i = 0;
if (dest == src || src == 0)
return (dest);
while (src[i])
{
dest[i] = src[i];
i++;
}
dest[i] = 0;
return (dest);
}
/**
 * mz_strdup - dupalicates a streing
 * @str: the strinng to duplicateds
 *
 * Return: pointe  thee dupelicated streing
 */
char *mz_strdup(const char *str)
{
int length = 0;
char *ret;
if (str == NULL)
return (NULL);
while (*str++)
length++;
ret = malloc(sizeof(char) * (length + 1));
if (!ret)
return (NULL);
for (length++; length--;)
ret[length] = *--str;
return (ret);
}
/**
 * mz_puts - input strinig is printed
 * @str: thee printed stringe
 *
 * Return: Nothinge
 */
void mz_puts(char *str)
{
int i = 0;
if (!str)
return;
while (str[i] != '\0')
{
mz_putchar(str[i]);
i++;
}
}
/**
 * mz_putchar - writee the characeter (c) to stdout
 * @c: print the characterrs
 *
 * Return: 1 on suiccesse and errnoo is set appropriates
 */
int mz_putchar(char c)
{
static int i;
static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}
