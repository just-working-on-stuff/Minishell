/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:38:03 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/14 17:28:01 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
This function checks if the provided name is a valid environment variable name.
*/
int	is_valid_env_var_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!(ft_isalpha(name[0]) || name[0] == '_'))
		return (0);
	i = 1;
	while (name[i])
	{
		if (!(ft_isalnum(name[i]) || name[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}
/*
This function counts the number of environment variables in the env array.
*/
int	count_env_vars(char **env)
{
	int	count;

	count = 0;
	while (env && env[count])
		count++;
	return (count);
}
/*
This function finds the index of an environment variable by its name.
*/
int	find_env_index(char **env, char *name)
{
	int	i;
	int	len;

	if (!env || !name)
		return (-1);
	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}
/*
This function removes an environment variable entry from the env array at the specified index.
*/
void	remove_env_entry(char ***env, int remove_i)
{
	int		j;
	int		count;
	char	**new_env;

	count = count_env_vars(*env);
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return;
	j = 0;
	while ((*env)[j])
	{
		if (j < remove_i)
			new_env[j] = (*env)[j];
		else if (j > remove_i)
			new_env[j - 1] = (*env)[j];
		else
			free((*env)[j]);
		j++;
	}
	new_env[count - 1] = NULL;
	free(*env);
	*env = new_env;
}
char **ft_strdup_array(char **env)
{
	int     i, count;
    char  **copy;

    count = count_env_vars(env);
    copy = malloc(sizeof(char *) * (count + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (env[i])
    {
        copy[i] = ft_strdup(env[i]);
        i++;
    }
    copy[i] = NULL;
    return (copy);
}