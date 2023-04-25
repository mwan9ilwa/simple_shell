#include "shell.h"

/**
 * @interactive: - returns true if shell is in the interactive mode state
 * @info: structure contains input and output files
 * @return: Returns 1 if in interactive mode, else return 0
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * @is_delimeter: - checks if character is a delimeter
 * @c: this is the char to check
 * @delim: this is the delimeter string
 * @return: return 1 if true, else return 0 if false
 */
int is_delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * @_isalphabet: - will check for alphabetic characters in the code
 * @c: This is the character to input
 * @return: returns 1 if alphabet, else return 0 if not
 */
int _isalphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * @_atoi: -  that converts a string of characters representing
 * an integer into an actual integer value.
 * @s: is the string to be converted
 * @return: 0 if no numbers in string, converted number
 * otherwise return the variable as is.
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}