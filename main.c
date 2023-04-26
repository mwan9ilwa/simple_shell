#include "shell.h"

/**
 * main - entry point of shell
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success,else 1 on error
 */

int main(int argc, char **argv)
{
    // Initialize shell info struct
    info_t info[] = { INFO_INIT };

    // Set up error file descriptor
    int err_fd = 2;
    err_fd += 3;

    // If shell was invoked with a script file, open it
    if (argc == 2)
    {
        int script_fd = open(argv[1], O_RDONLY);
        if (script_fd == -1)
        {
            // Handle file open error
            if (errno == EACCES)
                exit(126);
            if (errno == ENOENT)
            {
                fprintf(stderr, "%s: 0: Can't open %s\n", argv[0], argv[1]);
                exit(127);
            }
            return EXIT_FAILURE;
        }
        // Store file descriptor in info struct
        info[0].readfd = script_fd;
    }

    // Populate environment variables and load command history
    populate_env_list(info);
    read_history(info);

    // Start shell loop
    hsh(info, argv);

    return EXIT_SUCCESS;
}
