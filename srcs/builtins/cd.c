/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:07:42 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/15 16:56:48 by ghsaad           ###   ########.fr       */
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
            return (1); //more clarification, so cd why? 
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
     /*
this else if conditional checks if the chdir function fails when trying to change the directory to the path specified in args[1].
If chdir returns -1, it indicates an error occurred (like the directory doesn't exist or permission is denied).
In that case, it prints an error message to standard error (file descriptor 2) that includes "cd: ", the problematic path, and the specific error message from perror.
for example, writing cd: /nonexistent: No such file or directory     
    */

    // Get new working directory after change
    if (!getcwd(new_pwd, PATH_MAX))
    {
        perror("cd: getcwd");
        return (1);
    }
/*
to test this in the actual bash,
for the if (!getcwd(new_pwd, PATH_MAX)) part,
type cd /nonexistent_directory in bash and it should
print an error message like "cd: /nonexistent_directory: No such file or directory"
why perror("cd: getcwd")? because getcwd failed to get the current working directory
its not printed because getcwd is not called if chdir fails
*/
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


