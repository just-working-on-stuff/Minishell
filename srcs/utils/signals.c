/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:49:30 by codespace         #+#    #+#             */
/*   Updated: 2025/09/10 11:51:46 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_shell_state *g_state = NULL;

static void	clear_rl_line(void)
{
	// reset cursor & tell readline we’re on a fresh line
	rl_on_new_line();
	// put "" into buffer, no new history entry, keep undo
	rl_replace_line("", 0); //0 = don’t add this replacement line to history,
							//1 = would add to history.
}


/* SIGINT = Ctrl-C while at the prompt */
static	void handle_sigint(int signo)
{
	(void)signo; /* we know which signal this handler is for */
	write(STDOUT_FILENO, "\n", 1); /* print a newline (async-signal-safe)    */
	rl_on_new_line();   
	rl_replace_line("", 0);
	rl_redisplay();
}

static 	void hsndle_sigquit(int signo)
{
	(void)signo;
}

void setup_parent_signals(t_shell_state *state)
{
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask); ///* start with an empty mask of blocked signals */
	sa.sa_flags = 0;	    ///* NO SA_RESTART (key to our no-global design) */
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = handle_sigqit;
	sigaction(SIGQUIT, &sa, NULL);

}

void	setup_child_signals(void)
{
	struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = SIG_DFL;        // restore defaults for external programs
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
}