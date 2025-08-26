#include "../include/minishell.h"

 #include <readline/readline.h>
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    (void)env;
    
    if (ac != 1)
    {
       return (1);
    }
    while(1)
    {
        char *buffer = readline("Sea Cow: ");
        printf("%s\n", buffer);
        //
    }
    
    
}

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