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
}	t_shell_state;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;



typedef struct s_cmd
{
	char	**argv; // array of args /0
	int		infile; // fd for input (default = STDIN_FILENO)
	int		outfile;// fd for output (default = STDOUT_FILENO)
	struct s_cmd	*next; // next command (after pipe)
}t_cmd;

typedef struct s_data
{
	//fil this up
}	t_data;


/* ===================== TOKENS ===================== */

# define TOK_CMD       0
# define TOK_ARG       1
# define TOK_PIPE      2
# define TOK_REDIR_IN  3
# define TOK_REDIR_OUT 4
# define TOK_APPEND    5
# define TOK_HEREDOC   6

/*================signals===============*/

void	setup_parent_signals(void);
void	setup_child_signals(void);
int run_simple_command(char *const argv[], char *const envp[], t_shell_state *state);

void disable_echoctl(void);

/* ===================== PARSING ===================== */

t_token *lexer(char *line);
t_cmd   *parser(t_token *tokens, char **envp);
char    *expand_value(char *word, char **envp, int last_exit);

void    free_token(t_token **list);
void    free_cmds(t_cmd *cmds);

// int     handle_heredoc(char *delimiter);
t_token *new_token(char *str, int type);
void add_token_back(t_token **lst, t_token *new);
// void    print_tokens(t_token *lst);
void parse_redir(t_cmd *cmd, t_token *tok);
t_cmd *parser(t_token *tokens, char **envp);
void	pars_word(t_cmd *cmd, t_token *tok);
void add_cmd_back(t_cmd **lst, t_cmd *new);
t_token *lexer(char *line);
t_cmd *new_cmd(void);



#endif
