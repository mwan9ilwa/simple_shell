#include "shell.h"
/**
 * main - the entry point of the shell
 * @ac: arg  is the argument
 * @av: arg is the argument vector
 *
 * Return: return 1 on error, 0 if successful
 */
int main(int ac, char **av)
{
info_t info[] = { INFO_INIT };
int fd = 2;
asm ("mov %1, %0\n\a"
"add $3, %0"
: "=r" (fd)
: "r" (fd));
if (ac == 2)
{
fd = open(av[1], O_RDONLY);
if (fd == -1)
{
if (errno == EACCES)
exit(126);
if (errno == ENOENT)
{
a_eputs(av[0]);
a_eputs(": 0: Can't open ");
a_eputs(av[1]);
a_eputchar('\n');
a_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;
}
a_populate_env_list(info);
a_read_history(info);
a_hsh(info, av);
return (EXIT_SUCCESS);
}
