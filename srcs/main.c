#include "minishell.h"
#include <readline/readline.h> // readline, rl_*
#include <readline/history.h>  // add_history

int main(int argc, char **argv, char **env)
{
    // t_data  data;
    char    *line;
    int     last_status = 0;       
	t_shell_state 	state;       /* NEW: track $? locally */
	
    (void)argc;
    (void)argv;
    (void)env;
    // init_data(&data, argc, argv);
    // if (!make_env(&data, env))
	//after fork = pid;
	state.active_child = 0;

    setup_parent_signals();               /* NEW: install parent signal handlers */

    while (1)
    {
        errno = 0;                        /* NEW: so we can detect EINTR from readline */
        line = readline("lolipop 🍭 $");
        if (line == NULL)
        {
            if (errno == EINTR)           /* NEW: Ctrl-C at prompt interrupted readline */
            {
                last_status = 130;        /* bash-compatible */
                continue;                 /* show a fresh prompt */
            }
            printf("exit\n");             /* Ctrl-D (EOF) */
            return last_status;           /* exit with last status */
        }

        if (*line != '\0')                /* NEW: only store non-empty lines */
            add_history(line);

        free(line);
    }
    return 0;
}
