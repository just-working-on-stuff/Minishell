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
# include <stdbool.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/* ===================== TOKENS ===================== */

# define TOK_CMD       0
# define TOK_ARG       1
# define TOK_PIPE      2
# define TOK_REDIR_IN  3
# define TOK_REDIR_OUT 4
# define TOK_APPEND    5
# define TOK_HEREDOC   6

/* ===================== ERROR MACROS ===================== */
// # define ERR_MALLOC 1
# define ERR_MALLOC "Memory allocation failed\n"

// # define ERR_PIPE 	1
# define ERR_PIPE 	"Pipe creation failed\n"

// # define ERR_FORK 	1
# define ERR_FORK 	"Fork failed\n"

typedef struct s_token
{
    char *str;
    int type;
	struct s_token *prev;
	struct s_token *next;
}	t_token;

typedef struct s_list
{
	char			*str;
	struct s_list	*prev;
	struct s_list	*next;
}	t_list;

typedef struct s_shell_state
{
	int last_status;
	t_list	**env; // maybe change to char **env later
	t_token 	*token;
	pid_t	 active_child;
}	t_shell_state;


typedef struct s_cmd
{
	bool	skip_cmd;
	char	**argv; // array of args /0
	int		infile; // fd for input (default = STDIN_FILENO)
	int		outfile;// fd for output (default = STDOUT_FILENO)
	struct s_cmd	*next; // next command (after pipe)
	struct s_cmd	*prev; // next command (after pipe)
}	t_cmd;


typedef struct s_data
{
	t_list		*env;
	t_cmd		*cmds;
	t_token		*token;
	int			exit_code;
	int			pip[2];
	bool		sq;
	// char        *str;
    // t_list     *prev;
    // t_list     *next;

}	t_data;


// Add these to your existing minishell.h
/*=================== ENV LINKED LIST ==================*/
typedef struct s_env
{
	char			*key;
	char			*value;
	int				exported;
	struct s_env	*next;
}	t_env;


// utils
int	append_to_list(t_list **list, char *elem);
size_t list_length(t_list *list);
int	free_list(t_list **list);

char	**lst_to_arr(t_list *env);
// static void	ft_swap_str_tab(int i, int j, char **tab);
void	sort_array(char **arr, int len);



//env conversion
t_env	*env_array_to_list(char **env_array);
char	**env_list_to_array(t_env *env_list);
void	free_env_list(t_env *env_list);

//handlebuiltins
int	handle_builtins(char *expanded, t_shell_state *state);


/*=================== CD =================*/
char	*get_home_from_env(char **envp);
int		handle_cd_home(char **envp);
int		handle_cd_prev(void);
void	update_last_dir(char *path);

/*=================== EXPORT =================*/
void	print_export_error(char *arg);
void	print_export_alloc_error(void);
void	parse_export_args(char *expanded, char **args);

/*=================== UTILS =================*/
void	free_str_array(char **array);
char	**dup_str_array(char **array);
void	skip_spaces(char **str);
char	*extract_arg(char *start, char *end);

/*================signals===============*/

void	setup_parent_signals(void);
void	setup_child_signals(void);
int		run_simple_command(char *const argv[], char *const envp[], t_shell_state *state);

void	disable_echoctl(void);

/* ===================== PARSING ===================== */

t_token		*lexer(char *line);
t_cmd		*parser(t_token *tokens, char **envp);
char		*expand_value(char *word, char **envp, int last_exit);
void		free_token(t_token **list);
void		free_cmds(t_cmd *cmds);

// int     handle_heredoc(char *delimiter);
t_token		*new_token(char *str, int type);
void		add_token_back(t_token **lst, t_token *new);
// void    print_tokens(t_token *lst);
t_cmd		*parser(t_token *tokens, char **envp);
void parse_redir(t_cmd *cmd, t_token *tok, t_data *data);
void		pars_word(t_cmd *cmd, t_token *tok);
void 		add_cmd_back(t_cmd **lst, t_cmd *new);
t_token		*lexer(char *line);
t_cmd		*new_cmd(void);

//list_token.c
int			append_token(t_token **list, char *str, int type);
void		free_token(t_token **list);
char	*read_full_line(void);   /* your function */
int		shell_step(t_data *data);
void	shell_teardown(t_data *data);
int	has_unclosed_quote(const char *line);
int get_quoted_str(char *line, int i, char **out);
int	handle_word(t_token **head, char *line, int i);
char *expand_value(char *word, char **envp, int last_exit);
int	append_part(char **word, char *part);
char	*extract_var_name(char *str, int start);
char *find_env_value(char *key, char **envp);
char	*expand_tilde(char *word, char **envp);
char	*ft_strjoin_free(char *s1, char *s2);
int	exec_exit(char **argv, t_shell_state *state);
int	ft_strcmp(const char *s1, const char *s2);


int	exec_unset(char **argv, t_shell_state *state);
void	remove_env_entry(char ***env, int remove_i);
int	find_env_index(char **env, char *name);
int	count_env_vars(char **env);
int	is_valid_env_var_name(char *name);
char **ft_strdup_array(char **env);

/* ===================== EXECUTION ===================== */
bool	exec_pipeline(t_data *data);
void	child_process(t_data *data, t_cmd *cmd, int *pip);
char	*find_cmd(t_data *data, char *cmd);
int		handle_heredoc(char *delimiter, t_data *data);
void	parse_redir(t_cmd *cmd, t_token *tok, t_data *data);

/* ===================== SHELL EXECUTION ===================== */
bool	shell_parse_line(t_data *data, char *line);
bool	shell_exec(t_data *data);
void	shell_cleanup(t_data *data);

//export

bool	export(char *str, t_list **env);
int	ft_export(char **str, t_list **env);
int	ft_echo(char **args);
int	ft_pwd(void);
int ft_env(char **envp);
int	ft_cd(char **args, t_list **env);
int update_env(char ***envp, const char *key, const char *value);
int handle_cd_path(char *path);

bool	print_error(char *str);

//? these are static functions wich means there are only ued within one .c scope
//?so adding them to the header is wrong its either the functons are not static
//? and are allowed to be called outside the scope or are ststic and not added to the .h file

#endif
