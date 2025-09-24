#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char            *line;
    int             last_status = 0;       
    t_shell_state   state;       /* track $? locally */

    (void)argc;
    (void)argv;
    (void)env;

    state.active_child = 0;      /* initialize: 0 = at prompt */
    setup_parent_signals();
    disable_echoctl();           /* install parent signal handlers */

    while (1)
    {
        errno = 0;
        line = readline("lolipop 🍭$ ");
        if (line == NULL)
        {
            if (errno == EINTR)   /* Ctrl-C at prompt */
            {
                last_status = 130;
                continue;
            }
            return last_status;
        }

        if (*line != '\0')
            add_history(line);

        /* 🔹 Later: send line to parser instead of debug lexer */

        free(line);
    }
    return 0;
}


