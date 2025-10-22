/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:08:52 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/22 14:35:35 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env_list(t_env *head)
{
	t_env	*current;
	char	*temp_key;
	char	*temp_value;
	int		swapped;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = head;
		while (current && current->next)
		{
			if (ft_strcmp(current->key, current->next->key) > 0)
			{
				temp_key = current->key;
				temp_value = current->value;
				current->key = current->next->key;
				current->value = current->next->value;
				current->next->key = temp_key;
				current->next->value = temp_value;
				swapped = 1;
			}
			current = current->next;
		}
	}
}

int	sort_print(t_env *env_list, int fd)
{
	t_env	*sorted_list;

	sorted_list = env_dup_list(env_list);
	if (!sorted_list)
		return (1);
	sort_env_list(sorted_list);
	print_export(sorted_list, fd);
	env_clear_list(&sorted_list);
	return (0);
}

int	process_export_arg(char *arg, t_env **env_list)
{
	char	*key;
	char	*value;
	t_env	*existing;

	key = extract_key(arg);
	value = extract_value(arg);
	if (!key)
		return (1);
	existing = env_find_node(*env_list, key);
	if (existing)
		env_update_node(existing, value);
	else
	{
		existing = env_new_node(key, value);
		if (!existing)
		{
			free(key);
			free(value);
			return (1);
		}
		env_add_back(env_list, existing);
	}
	free(key);
	free(value);
	return (0);
}

int	ft_export(char **args, t_env **env_list)
{
	int	i;
	int	fd;
	int	status;

	fd = 1;
	if (args[1] == NULL)
		return (sort_print(*env_list, fd));
	i = 1;
	status = 0;
	while (args[i])
	{
		if (!validate_export(args[i]))
		{
			ft_putstr_fd("export: invalid variable name\n", 2);
			status = 1;
		}
		else if (process_export_arg(args[i], env_list) != 0)
		{
			ft_putstr_fd("export: memory allocation failed\n", 2);
			status = 1;
		}
		i++;
	}
	return (status);
}