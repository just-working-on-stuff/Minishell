#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>          // printf
# include <readline/readline.h> // readline, rl_*
# include <readline/history.h>  // add_history
// #include <readline/readline.h>
// #include <readline/history.h>

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h> 
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token
{
    char *str;
    int type;
	struct s_token *prev;
	struct s_token *next;
}	t_token;

typedef struct s_shell_state
{
	int last_status;
	char **env;
	t_token 	*token;
	pid_t	 active_child;
	// sig_atomic_t  got_sigint;
}	t_shell_state;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_data
{
	//fil this up
}	t_data;

void	setup_parent_signals(void);
void	setup_child_signals(void);
int run_simple_command(char *const argv[], char *const envp[], t_shell_state *state);

void disable_echoctl(void);
#endif
