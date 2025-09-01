#include "../include/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_shell_state	state;
	char			*prompt;
	char			*buffer;

	(void)av;
	(void)envp;
	state.last_status = 0;
	state.env = NULL;
	state.token = NULL;
	if (ac != 1)
	{
		printf("Hint: you need to write ./minishell alone\n");
		return (1);
	}
	while (1)
	{
		prompt = get_prompt(&state);       /* must return malloc'ed string */
		buffer = readline(prompt);
		free(prompt);
		if (buffer == NULL)                /* Ctrl-D */
		{
			printf("exit\n");
			exit(state.last_status);
		}
		if (is_blank_line(buffer))         /* skip blanks */
		{
			free(buffer);
			continue ;
		}
		add_history(buffer);               /* history keeps its own copy */
		/* TODO: tokenize/expand/exec here; update state.last_status */
		free(buffer);
	}
}

//Mariams notes
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