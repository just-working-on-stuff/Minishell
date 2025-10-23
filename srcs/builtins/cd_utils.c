/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:15:53 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/23 12:16:25 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_from_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "HOME=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

int	handle_cd_home(char **envp)
{
	char	*home;

	home = get_home_from_env(envp);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (handle_cd_path(home));
}


static char	*get_last_dir(void)
{
	static char	last_dir[PATH_MAX];

	return (last_dir);
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
	if (handle_cd_path(last_dir))
		return (1);
	printf("%s\n", last_dir);
	return (0);
}

void	update_last_dir(char *path)
{
	char	*last_dir;

	last_dir = get_last_dir();
	ft_strlcpy(last_dir, path, PATH_MAX);
}