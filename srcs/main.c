#include "minishell.h"

static void print_cmds(t_cmd *cmds)
{
    int i;

    while (cmds)
    {
        printf("CMD:\n");
        if (cmds->argv)
        {
            i = 0;
            while (cmds->argv[i])
            {
                printf("  argv[%d] = %s\n", i, cmds->argv[i]);
                i++;
            }
        }
        printf("  infile  = %d\n", cmds->infile);
        printf("  outfile = %d\n", cmds->outfile);
        cmds = cmds->next;
    }
}

int main(int argc, char **argv, char **env)
{
    char            *line;
    int             last_status = 0;       
    t_shell_state   state;       /* track $? locally */
    t_token         *tokens;     /* for lexer */
    t_cmd           *cmds;       /* for parser */

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

        /* 🔹 Tester hook */
        tokens = lexer(line);
        cmds = parser(tokens, env);
        print_cmds(cmds);
        free_token(&tokens);
        free_cmds(cmds);

        free(line);
    }
    return 0;
}
