/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:00:00 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/27 20:00:00 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

static char	*get_last_dir(void)
{
	static char	last_dir[PATH_MAX];

	return (last_dir);
}

void	update_last_dir(char *path)
{
	char	*last_dir;

	last_dir = get_last_dir();
	ft_strlcpy(last_dir, path, PATH_MAX);
}

int	handle_cd_prev(void)
{
	char	*last_dir;

	last_dir = get_last_dir();
	if (last_dir[0] == '\0')
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	if (handle_cd_with_path(last_dir))
		return (1);
	printf("%s\n", last_dir);
	return (0);
}

char	*create_env_var_string(char *key, char *value)
{
	char	*new_var;
	char	*temp;

	if (!key || !value)
		return (NULL);
	new_var = ft_strjoin(key, "=");
	if (!new_var)
		return (NULL);
	temp = ft_strdup(value);
	if (!temp)
	{
		free(new_var);
		return (NULL);
	}
	new_var = ft_strjoin_free(new_var, temp);
	return (new_var);
}
