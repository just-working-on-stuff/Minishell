/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 19:25:26 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/22 14:08:17 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

bool	validate_export(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (false);
	while (str[i] != '\0' && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

char	*extract_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(i + 1);
	if (!key)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*extract_value(char *str)
{
	char	*equal_pos;
	char	*value;

	equal_pos = ft_strchr(str, '=');
	if (!equal_pos)
		return (NULL);
	value = ft_strdup(equal_pos + 1);
	return (value);
}

void	print_export(t_env *env_list, int fd)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(current->key, fd);
		if (current->value)
		{
			ft_putstr_fd("=\"", fd);
			ft_putstr_fd(current->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
		current = current->next;
	}
}

t_env	*env_dup_list(t_env *head)
{
	t_env	*new_head;
	t_env	*current;
	t_env	*new_node;

	new_head = NULL;
	current = head;
	while (current)
	{
		new_node = env_new_node(current->key, current->value);
		if (!new_node)
		{
			env_clear_list(&new_head);
			return (NULL);
		}
		new_node->exported = current->exported;
		env_add_back(&new_head, new_node);
		current = current->next;
	}
	return (new_head);
}
