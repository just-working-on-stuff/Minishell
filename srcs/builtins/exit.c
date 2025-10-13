/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:04:05 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/13 16:20:24 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static int	is_numeric_str(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	if (s[0] == '+' || s[0] == '-')
		s++;
	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	exec_exit(char **argv, t_shell_state *state)
{
	ft_putstr_fd("exit\n", 1);
	if (!argv[1])
		exit(state->last_status);
	if (!is_numeric_str(argv[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		exit(255);
	}
	if (argv[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		state->last_status = 1;
		return (1);
	}
	exit(ft_atoi(argv[1]) % 256);
}

