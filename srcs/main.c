#include "minishell.h"

int main(int argc, char **argv, char **env)
{
    char            *line;
    char            *expanded;
    int             last_status;       
    t_shell_state   state;       /* track $? locally */

    (void)argc;
    (void)argv;
    (void)env;

    state.active_child = 0;
    last_status = 42; // simulate last exit code
    setup_parent_signals();
    disable_echoctl();

    while (1)
    {
        errno = 0;
        line = read_full_line();
        if (!line)
        {
            if (errno == EINTR)   /* Ctrl-C at prompt */
            {
                last_status = 130;
                continue;
            }
            return (last_status); /* Ctrl-D at main prompt exits */
        }
        if (*line != '\0')
            add_history(line);

        /* 🔹 Test expander */
        expanded = expand_value(line, env, last_status);
        if (expanded)
        {
            printf("Expanded: [%s]\n", expanded);
            free(expanded);
        }

        /* 🔹 Later: send line to lexer + parser */
        // tokens = lexer(line);
        // cmds = parser(tokens, env);
        // execute(cmds, &state);

        free(line);
    }
    return (0);
}
