/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:49:30 by codespace         #+#    #+#             */
/*   Updated: 2025/09/16 15:26:39 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


/* SIGINT = Ctrl-C while at the prompt */
static	void handle_sigint(int signo)
{
	(void)signo; /* we know which signal this handler is for */
	write(STDOUT_FILENO, "\n", 1); /* print a newline (async-signal-safe)    */
	rl_on_new_line();   
	rl_replace_line("", 0);
	rl_redisplay();
}

static 	void handle_sigqit(int signo)
{
	(void)signo;
}

void setup_parent_signals(void)
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