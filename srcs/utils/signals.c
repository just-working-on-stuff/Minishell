/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:17:19 by aalbugar          #+#    #+#             */
/*   Updated: 2025/09/23 11:34:35 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_sigint(int signo)
{
    (void)signo;
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

/* PARENT: install handlers */
void setup_parent_signals(void)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    /* SIGINT (Ctrl-C): no SA_RESTART so readline returns with EINTR */
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags   = 0;
    sa_int.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa_int, NULL);

    /* SIGQUIT (Ctrl-\): IGNORE so readline doesn't get interrupted → no jump */
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags   = SA_RESTART;     /* harmless; ensures syscalls restart if any */
    sa_quit.sa_handler = SIG_IGN;
    sigaction(SIGQUIT, &sa_quit, NULL);

    /* (optional) also ignore Ctrl-Z so shell doesn't suspend */
    struct sigaction sa_tstp;
    sigemptyset(&sa_tstp.sa_mask);
    sa_tstp.sa_flags   = SA_RESTART;
    sa_tstp.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa_tstp, NULL);
}

/* CHILD: restore defaults before execve */
void setup_child_signals(void)
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags   = 0;
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT,  &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGTSTP, &sa, NULL);
}
