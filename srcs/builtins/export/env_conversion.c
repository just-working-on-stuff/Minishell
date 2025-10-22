/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:23:24 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/22 18:40:14 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Convert char ** environment to t_env * linked list
t_env	*env_array_to_list(char **env_array)
{
	t_env	*env_list;
	t_env	*new_node;
	char	*equal_pos;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (env_array && env_array[i])
	{
		equal_pos = ft_strchr(env_array[i], '=');
		if (equal_pos)
		{
			key = malloc(equal_pos - env_array[i] + 1);
			if (!key)
				return (env_clear_list(&env_list), NULL);
			ft_strlcpy(key, env_array[i], equal_pos - env_array[i] + 1);
			value = ft_strdup(equal_pos + 1);
			if (!value)
				return (free(key), env_clear_list(&env_list), NULL);
			new_node = env_new_node(key, value);
			free(key);
			free(value);
			if (!new_node)
				return (env_clear_list(&env_list), NULL);
			env_add_back(&env_list, new_node);
		}
		i++;
	}
	return (env_list);
}

// Convert t_env * linked list back to char ** environment
char	**env_list_to_array(t_env *env_list)
{
	t_env	*current;
	char	**env_array;
	char	*temp;
	int		count;
	int		i;

	count = 0;
	current = env_list;
	while (current && ++count)
		current = current->next;
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	current = env_list;
	while (current)
	{
		if (current->value)
		{
			temp = ft_strjoin(current->key, "=");
			env_array[i] = ft_strjoin(temp, current->value);
			free(temp);
		}
		else
			env_array[i] = ft_strdup(current->key);
		if (!env_array[i])
		{
			while (--i >= 0)
				free(env_array[i]);
			free(env_array);
			return (NULL);
		}
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env_list(t_env *env_list)
{
	env_clear_list(&env_list);
}