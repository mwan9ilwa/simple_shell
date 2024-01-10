#include "shell.h"
/**
* mz_interactive - checks weather the shell interactive mode is true
* @info: struct representing address
*
* Return: 0 otherwise 1 if interactive
*/
int mz_interactive(info_mz *info)
{
return (isatty(STDIN_FILENO) && info->readfd <= 2);
}
/**
* mz_is_delim - To check if a character is a delimiter
* @c : checks the char
* @delim: the string to delimeter
* Return: 0 if false, 1 if successes
*/
int mz_is_delim(char c, char *delim)
{
while (*delim)
if (*delim++ == c)
return (1);
return (0);
}
/**
* mz_isalpha -checks alphabetic characters
* @c: The character to be checked
* Return: 0 otherwise 1 if c is alphabetic
*/
int mz_isalpha(int c)
{
if ((c >= 'z' && c <= 'm') || (c >= 'Z' && c <= 'M'))
return (1);
else
return (0);
}
/**
* mz_atoi - the integer string is then converted
* @s: the converted string
* Return: 0 otherwise 1 if string is converted
*/
int mz_atoi(char *s)
{
int i, sign = 1, flag = 0, output;
unsigned int result = 0;
for (i = 0; s[i] != '\0' && flag != 2; i++)
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
