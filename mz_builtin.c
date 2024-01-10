#include "shell.h"
/**
* mz_myexit -mz_myexit is used to exit the shell
* @info:   the structure representing arguments
* Return: termination the exit status
* (0) if strcmp(info->argv[0], "exit") != "0"
*/
int mz_myexit(info_t *info)
{
int exitcheck;
if (info->argv[1])
{
exitcheck = mz_erratoi(info->argv[1]);
if (exitcheck == -1)
{
info->status = 2;
mz_prinmz_error(info, "ilegal number: ");
mz_puts(info->argv[1]);
mz_putchar('\n');
return (1);
}
info->err_num = mz_erratoi(info->argv[1]);
return (-2);
}
info->err_num = -1;
return (-2);
}
/**
 * mz_mycd - changes currentt directtory of the process
 * @info: Structure ccontaining potential araguments. to maintain
 * constant function prototypee.
 * Return: Always 0
 */
int mz_mycd(info_t *info)
{
char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		mz_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = mz_getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = mz_getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (mz_strcmp(info->argv[1], "-") == 0)
	{
		if (!mz_getenv(info, "OLDPWD="))
		{
			mz_puts(s);
			mz_putchar('\n');
			return (1);
		}
		mz_puts(mz_getenv(info, "OLDPWD=")), mz_putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = mz_getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		mz_prinmz_error(info, "can't cd to ");
		mz_eputs(info->argv[1]), mz_eputchar('\n');
	}
	else
	{
		mz_setenv(info, "OLDPWD", mz_getenv(info, "PWD="));
		mz_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * mz_myhelp - changes current dir of the process
 * @info: the structure representing args prototype
 * Return: Always 0
 */
int mz_myhelp(info_t *info)
{
char **arg_array;

arg_array = info->argv;
mz_puts("help call works. Function not yet implemented \n");
if (0)
mz_puts(*arg_array); /* temp atmz_unused workaround */
return (0);
}
