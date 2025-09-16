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
#include <errno.h>	//errno, EINTR

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

#endif
