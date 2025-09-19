#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    // t_data  data;
    char            *line;
    int             last_status = 0;       
    t_shell_state   state;       /* NEW: track $? locally */
	
    (void)argc;
    (void)argv;
    (void)env;
    // init_data(&data, argc, argv);
    // if (!make_env(&data, env))
	//after fork = pid;
    state.active_child = 0;      /* initialize: 0 = at prompt */
    setup_parent_signals();
	disable_echoctl();       /* NEW: install parent signal handlers */

    while (1)
    {
        errno = 0;                        /* NEW: so we can detect EINTR from readline */
        line = readline("lolipop 🍭$ ");
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

        /* 🔹 TEST HOOK: run /bin/echo hello */
        if (line && line[0] == 't')   /* type 't' at prompt to test */
        {
            char *const av[] = {"/bin/echo", "hello", NULL};
            last_status = run_simple_command(av, env, &state);
            printf("last_status = %d\n", last_status);  /* debug print */
        }

        free(line);
    }
    return 0;
}
