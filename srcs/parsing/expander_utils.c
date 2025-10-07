/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:23:43 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/07 14:44:27 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *find_env_value(char *key, char **envp)
{
	int i;
	int len;

	if(!key || !envp)
		return(NULL);
	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*extract_var_name(char *str, int start)
{
	int		i;
	int		len;

	i = start + 1; // skip the '$'
	if (str[i] == '?')
		return (ft_strdup("?"));
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (ft_strdup("")); // invalid var name like $1, $!, $-, just skip

	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	len = i - (start + 1);
	return (ft_substr(str, start + 1, len));
}
