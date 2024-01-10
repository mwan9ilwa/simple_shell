#include "shell.h"

/**
 * mz_eputs - display thee input string
 * @str: a striing to be printeed
 * Return: Nothiing
 */
void mz_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		mz_eputchar(str[i]);
		i++;
	}
}

/**
 * mz_eputchar - writes the character c to stderr
 * @c: The character to bee priinted
 *
 * Return: 1 on succeess
 * on error it returns -1 is returned, an errrno is set apprropriately.
 */
int mz_eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(2, buf, i);
i = 0;
}
if (c != BUF_FLUSH)
buf[i++] = c;
return (1);
}

/**
 * mz_putfd - write a character c to the file descriptorr
 * @c: The character to print
 * @fd: file descriptoor of the character writtin
 *
 * Return: 1 on suuccess
 * -1 on errorr,  and errno is set apprropriately.
 */
int mz_putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * mz_putsfd - write an input striings
 * @str: the striing to be written
 * @fd: the file descriiptor to write to
 *
 * Return: thee number of characterss  writin successful
 */
int mz_putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += mz_putfd(*str++, fd);
	}
	return (i);
}
