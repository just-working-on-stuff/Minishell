/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:50:15 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/27 19:48:39 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_node(t_list **env, char *name)
{
	t_list	*current;
	t_list	*prev;
	int		name_len;

	if (!env || !*env || !name)
		return ;
	name_len = ft_strlen(name);
	current = *env;
	prev = NULL;
	while (1)
	{
		if (ft_strncmp(current->str, name, name_len) == 0
			&& (current->str[name_len] == '=' || current->str[name_len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->str);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
		if (current == *env)
			break ;
	}
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
			remove_env_node(state->env, argv[i]);  // ← FIXED: removed the &
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