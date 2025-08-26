#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdio.h>
#include "../libft/libft.h"


typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC,
	PIPE,
	LOGIC_AND,
	LOGIC_OR,
	BRACKET,
	COMMAND,
	ARGUMENT,
	FILENAME,
	DELIMITER
}						t_token_type;

typedef struct s_token
{
    char *value;
    int type;
}   t_token;

typedef struct s_shell_state
{
  int last_status;
  char **env;
    t_token *token;

}   t_shell_state;


#endif
