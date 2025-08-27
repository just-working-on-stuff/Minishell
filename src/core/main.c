#include "../include/minishell.h"

int main(int ac, char **av, char **env)
{
    (void)av;
    (void)env;
    
    t_shell_state state;
    state.last_status = 0;
    if (ac != 1)
    {
        printf("Hint: you need to write ./minishell alone\n");
        return (1);
    }
    while(1)
    {
        char *prompt = get_prompt(&state);   /* NEW */
        char *buffer = readline(prompt);     /* NEW */
        free(prompt);                        /* NEW */

        if (buffer == NULL)
        {
            printf("exit\n");
            exit(state.last_status);
        }
        if (isspace(buffer))
        {
            free(buffer);
            continue;
        }
        else
            add_history(buffer);
    }
}


// int main(int ac, char **av, char **env)
// {
//     (void)av;
//     (void)env;
    
//     t_shell_state state;
//     state.last_status = 0;
//     if (ac != 1)
//     {
//         printf("Hint: you need to write ./minishell alone\n");
//         return (1);
//     }
//     while(1)
//     {
//         char *buffer = readline("Sea Cow: ");
//         if (buffer == NULL)
//         {
//             printf("exit\n");
//             exit(state.last_status);
//         }
//         if (isspace(buffer))
//         {
//             free(buffer);
//             continue;
//         }
//         else
//             add_history(buffer);
//     }
// }

// t_token *token;

// token->value = "echo";
// token->type = COMMAND;

// if (token->type = COMMAND)
// {
//     execute;
// }
// if (token == REDIRECT_APPEND)
// {
//     redirect;
// } 

//  echo hi && echo no > file
//  [echo] [WORD]  
// rename -> 