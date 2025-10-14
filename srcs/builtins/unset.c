/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:50:15 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/14 13:52:22 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
This function removes an environment variable from the env array at the specified index.
*/
static void	unset_env_var(char *name, char ***env)
{
	int	index;

	if (!env || !*env)
		return;
	index = find_env_index(*env, name);
	if (index == -1)
		return;
	remove_env_entry(env, index);
}
/*
This function implements the unset builtin command.
*/
int	exec_unset(char **argv, t_shell_state *state)
{
	int	i;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv[i])
	{
		if (is_valid_env_var_name(argv[i]))
			unset_env_var(argv[i], &state->env);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		i++;
	}
	return (0);
}
