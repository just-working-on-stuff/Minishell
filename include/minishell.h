#ifndef MINISHELL_H
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>          // printf
#include <stdlib.h>         // malloc, free, exit
#include <unistd.h>         // fork, execve, pipe, dup, dup2, isatty, ttyname, ttyslot, getcwd, chdir, close, write, access
#include <fcntl.h>          // open
#include <sys/types.h>      // pid_t, mode_t
#include <sys/wait.h>       // wait, waitpid, wait3, wait4
#include <signal.h>         // signal, sigaction, sigemptyset, sigaddset, kill
#include <sys/stat.h>       // stat, lstat, fstat, unlink
#include <dirent.h>         // opendir, readdir, closedir
#include <errno.h>          // errno, perror, strerror
#include <termios.h>        // tcsetattr, tcgetattr
#include <termcap.h>        // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
#include <sys/ioctl.h>      // ioctl
#include <readline/readline.h> // readline, rl_*
#include <readline/history.h>  // add_history


typedef enum e_token_type
{
	WORD,
	REDIRECT_IN,
	REDIRECT_OUT,
	REDIRECT_APPEND,
	HEREDOC, //(<<) → special redirection: feed a block of text until a delimiter line.
	PIPE,
	LOGIC_AND,
	LOGIC_OR,
	BRACKET,
	COMMAND,
	ARGUMENT,
	FILENAME,
	DELIMITER
}						t_token_type;

// typedef struct s_token
// {
//     char *value;
//     int type;
// }   t_token;

// typedef struct s_shell_state
// {
//   int last_status;
//   char **env;
//     t_token *token;

// }   t_shell_state;

// char *get_prompt(t_shell_state *state);
// static char *build_interactive_prompt(void);
// static char *build_from_dir(const char *dir);

// /*Utilities*/
// int	is_blank_line(const char *s);
// int	ft_isspace(int c);


#endif
