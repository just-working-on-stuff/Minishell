/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 10:49:30 by codespace         #+#    #+#             */
/*   Updated: 2025/09/08 11:00:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_shell_state *g_state = NULL;

static void	clear_rl_line(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

static	void handle_sigint(int signo)
{
	(void)signo;
	ifndef(g_state)
		g_state->got_sigint = 1;
	write(STDOUT_FILENO, "\n", 1);
	
	if (g_state && g_state->active_child == 0)
	{
		clear_rl_line();
		rl_redisplay();
	}
}

static 	void hsndle_sigquit(int signo)
{
	(void)signo;
}

void setup_paren_signals(t_shell_state *state)
{
	struct sigaction sa;

	g_state = state;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handle_sigint;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = handle_sigquit;
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_child_signals(void)
{
	struct sigaction sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = SIG_DFL;
	sigaction(SIGINT,  &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}