/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:07:42 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/13 16:25:35 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(char **args)
{
    char old_pwd[PATH_MAX];
    char new_pwd[PATH_MAX];

    // Store current directory before changing
    if (!getcwd(old_pwd, PATH_MAX))
    {
        perror("cd: getcwd");
        return (1);
    }

    // Handle no arguments (cd to HOME)
    if (!args[1])
    {
        char *home = getenv("HOME");
        if (!home)
        {
            ft_putstr_fd("cd: HOME not set\n", 2);
            return (1);
        }
        if (chdir(home) == -1)
        {
            perror("cd");
            return (1);
        }
    }
    // Handle cd with path argument
    else if (chdir(args[1]) == -1)
    {
        ft_putstr_fd("cd: ", 2);
        ft_putstr_fd(args[1], 2);
        ft_putstr_fd(": ", 2);
        perror("");
        return (1);
    }

    // Get new working directory after change
    if (!getcwd(new_pwd, PATH_MAX))
    {
        perror("cd: getcwd");
        return (1);
    }

    // Update PWD and OLDPWD environment variables
    // Note: You'll need to implement update_env() function
    update_env("OLDPWD", old_pwd);
    update_env("PWD", new_pwd);

    return (0);
}

/* 
this function implements cd in bash, it changes the current working directory
and keeps the pwd and oldpwd environment variables updated so that it knows where it is in
the system
*/

update_env(char *key, char *value)
{
    
}