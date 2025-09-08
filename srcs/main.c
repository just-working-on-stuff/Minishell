#include "../include/minishell.h"
#include <readline/readline.h> // readline, rl_*
#include <readline/history.h>  // add_history


int main(int argc, char **argv, char **env)
{
    // t_data  data;
    char    *line;
    (void)argc;
    (void)argv;
    (void)env;
    // init_data(&data, argc, argv);
    // if (!make_env(&data, env))
    while(1)
    {
        line = readline("lolipop 🍭 $");
        if (line == NULL)
            break;
        free(line);
    }
    return 0;
}