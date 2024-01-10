#include "shell.h"
/**
* a_myexit -a_myexit is used to exit the shell
* @info:   the structure representing arguments
* Return: termination the exit status
* (0) if strcmp(info->argv[0], "exit") != "0"
*/
int a_myexit(info_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = a_erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
a_prina_error(info, "ilegal number: ");
a_puts(info->argv[1]);
a_putchar('\n');
return (1);
}
info->err_num = a_erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
 * a_mycd - changes currentt directtory of the process
 * @info: Structure ccontaining potential araguments. to maintain
 * constant function prototypee.
 * Return: Always 0
 */
int a_mycd(info_t *info)
{
char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		a_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = a_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = a_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (a_strcmp(info->argv[1], "-") == 0)
	{
		if (!a_getenv(info, "OLDPWD="))
		{
			a_puts(s);
			a_putchar('\n');
			return (1);
		}
		a_puts(a_getenv(info, "OLDPWD=")), a_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = a_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		a_prina_error(info, "can't cd to ");
		a_eputs(info->argv[1]), a_eputchar('\n');
	}
	else
	{
		a_setenv(info, "OLDPWD", a_getenv(info, "PWD="));
		a_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * a_myhelp - changes current dir of the process
 * @info: the structure representing args prototype
 * Return: Always 0
 */
int a_myhelp(info_t *info)
{
char **arg_trray;

arg_trray = info->argv;
a_puts("help call works. Function not yet implemented \n");
if (0)
a_puts(*arg_trray); /* temp ata_unused workaround */
return (0);
}
