#include "shell.h"

/**
 * mz_erratoi - convertt a striing to an inteeger
 * @s: input striing to be converrted
 * Return: 0 if no presented numbers in string, otherwiise
 *       -1 on errorr
 */
int mz_erratoi(char *s)
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
 * mz_prinmz_error - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void mz_prinmz_error(info_mz *info, char *estr)
{
	mz_eputs(info->fname);
	mz_eputs(": ");
	mz_prinmz_d(info->line_count, STDERR_FILENO);
	mz_eputs(": ");
	mz_eputs(info->argv[0]);
	mz_eputs(": ");
	mz_eputs(estr);
}

/**
 * mz_prinmz_d - printss a deciimal (inteeger) number (basse 10)
 * @input: the inteeger to be printed
 * @fd: the integer input in filedescriptor
 *
 * Return: printed characteer numberrs
 */
int mz_prinmz_d(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar =  __putchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
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
 * mz_convermz_number - converteers a number usiing base
 * @num: number converteed
 * @base: base for conversiion
 * @flags: aragument flaags or options
 *
 * Return: a representing striing converrted numbeer
 */
char *mz_convermz_number(long int num, int base, int flags)
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
 * mz_remove_comments - replaces firrst instaance of '#' with '\0' in a striing
 * @buf: pointeer to a striing modify
 *
 * Return: 0 Always
 */
void mz_remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
