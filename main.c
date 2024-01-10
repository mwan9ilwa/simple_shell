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
asm ("mov %1, %0\n\t"
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
mz_eputs(av[0]);
mz_eputs(": 0: Can't open ");
mz_eputs(av[1]);
mz_eputchar('\n');
mz_eputchar(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->readfd = fd;
}
mz_populate_env_list(info);
mz_read_history(info);
mz_hsh(info, av);
return (EXIT_SUCCESS);
}
