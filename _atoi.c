#include "shell.h"

/**
 * @_interactive: - returns true if shell is in the interactive mode state.
 * @info: structure contains input and output files
 * @isatty: checking the standard input file descriptor (STDIN_FILENO)
 *  is a terminal
 */

int _interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * @_delimeter: - checks if character is a delimeter
 * @c: this is the char to check
 */
int _delimeter(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * @_alphabet: - will check for alphabetic characters in the code
 * @c: This is the character to input
 */

int _alphabet(int c)
{
if (isalpha(c)) {
    return 1;
} else {
    return 0;
}
}

/**
 * @_atoi: -  that converts a string of characters representing an integer into an actual integer value.
 * @s: is the string to be converted
 * @return: 0 if no numbers in string, converted number otherwise return the variable as is.
 */

int _atoi(char *s)
{
    int result = 0;
    int sign = 1;
    int i = 0;

    if (s[0] == '-') {
        sign = -1;
        i = 1;
    }

    for (; s[i] != '\0'; i++) {
        if (s[i] < '0' || s[i] > '9') {
            break;
        }
        result = result * 10 + (s[i] - '0');
    }

    return sign * result;
}
