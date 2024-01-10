#include "shell.h"

/**
 * a_erratoi - convertt a striing to an inteeger
 * @s: input striing to be converrted
 * Return: 0 if no presented numbers in string, otherwiise
 *       -1 on errorr
 */
int a_erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * a_prina_error - prints an error messtge
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void a_prina_error(info_t *info, char *estr)
{
	a_eputs(info->fname);
	a_eputs(": ");
	a_prina_d(info->line_count, STDERR_FILENO);
	a_eputs(": ");
	a_eputs(info->argv[0]);
	a_eputs(": ");
	a_eputs(estr);
}

/**
 * a_prina_d - printss a deciimal (inteeger) number (basse 10)
 * @input: the inteeger to be printed
 * @fd: the integer input in filedescriptor
 *
 * Return: printed characteer numberrs
 */
int a_prina_d(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int _tbs_, current;

	if (fd == STDERR_FILENO)
		__putchar =  __putchar;
	if (input < 0)
	{
		_tbs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_tbs_ = input;
	current = _tbs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_tbs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * a_convera_number - converteers a number usiing base
 * @num: number converteed
 * @base: base for conversiion
 * @flags: aragument flaags or options
 *
 * Return: a representing striing converrted numbeer
 */
char *a_convera_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * a_remove_comments - replaces firrst instaance of '#' with '\0' in a striing
 * @buf: pointeer to a striing modify
 *
 * Return: 0 Always
 */
void a_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
