/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:07:42 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/23 12:26:32 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int handle_cd_path(char *path)
{
    if (chdir(path) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(path, 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }
    return (0);
}
/*
this function creates a new environment variable string in the format "KEY=VALUE".
*/
static char *create_env_var(const char *key, const char *value)
{
    char    *new_var;
    size_t  key_len;

    key_len = ft_strlen(key);
    new_var = malloc(key_len + ft_strlen(value) + 2); //the two added bytes is for null and = sign
    if (!new_var)
        return (NULL);
    ft_strlcpy(new_var, key, key_len + 1); //visually, this would look like "KEY\0"
    new_var[key_len] = '='; //visually, this would look like "KEY=\0"
    ft_strlcpy(new_var + key_len + 1, value, ft_strlen(value) + 1); //visually, this would look like "KEY=VALUE\0"
    return (new_var); //so visually, this would look like "KEY=VALUE\0"
}
/*
this function adds a new environment variable to the envp array.
*/

static int add_new_env(char ***envp, char *new_var) 
{
    char    **new_envp;
    int     i;

    i = 0;
    while ((*envp)[i])
        i++;
    new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
        return (1);
    i = 0;
    while ((*envp)[i])
    {
        new_envp[i] = (*envp)[i];
        i++;
    }
    new_envp[i] = new_var;
    new_envp[i + 1] = NULL;
    free(*envp);
    *envp = new_envp;
    return (0);
}
/*
this function updates or adds an environment variable in the envp array.
*/

int update_env(char ***envp, const char *key, const char *value)
{
    int     i;
    char    *new_var;
    size_t  key_len;

    if (!envp || !*envp || !key || !value)
        return (1);
    key_len = ft_strlen(key);
    i = 0;
    while ((*envp)[i])
    {
        if (!ft_strncmp((*envp)[i], key, key_len) // this part compares between the key and the beginning
        // of the env var for the length of the key and the = sign ensures that we are matching the full key
        // so visually this would look like "KEY=" vs "KEYVALUE"
			&& (*envp)[i][key_len] == '=')
        {
            if (!(new_var = create_env_var(key, value))) // visually this would look like "KEY=VALUE\0"
                return (1);
            free((*envp)[i]);
            (*envp)[i] = new_var;// updating the env var in place, visually this would look like "KEY=VALUE\0"
            return (0);
        }
        i++;
    }
    if (!(new_var = create_env_var(key, value)))
        return (1);
    return (add_new_env(envp, new_var));
}

/*
this function implements the cd command, changing the current directory and updating PWD and OLDPWD.
*/

#include "minishell.h"

int	ft_cd(char **args, char ***envp)
{
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (!getcwd(old_pwd, PATH_MAX))
		return (perror("cd: getcwd"), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		if (handle_cd_home(*envp))
			return (1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (handle_cd_prev())
			return (1);
	}
	else if (handle_cd_path(args[1]))
		return (1);
	if (!getcwd(new_pwd, PATH_MAX))
		return (1);
	update_last_dir(old_pwd);
	return (update_env(envp, "OLDPWD", old_pwd)
		|| update_env(envp, "PWD", new_pwd));
}
// this function handles the 'cd' command, changing the current directory and updating the PWD and OLDPWD environment variables accordingly.
// */


/*
so, the whole cd command works as follows:
1. It first retrieves the current working directory and stores it in old_pwd.
2. It then checks if a target directory is provided as an argument. If not, it attempts to change to the HOME directory.
3. If a target directory is provided, it attempts to change to that directory.
4. After changing the directory, it retrieves the new current working directory and stores it in new_pwd.
5. Finally, it updates the OLDPWD and PWD environment variables to reflect the change in directories.
*/

/*
this function starts from ft_cd, then calls update_env(briefly, it checks if the env var exists),
which may call create_env_var(briefly, it creates the new env var string, like KEY=VALUE)
and add_new_env(briefly, it adds the new env var to the envp array if it doesn't exist)
then the flow returns back up to ft_cd.
*/