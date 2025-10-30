/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:00:00 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/30 18:30:17 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_dir(char **path, char *cmd, t_data *data)
{
	struct stat	path_stat;

	stat(*path, &path_stat);
	if (!S_ISREG(path_stat.st_mode))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		data->exit_code = 126;
		return (false);
	}
	return (true);
}

// static bool	cmd_exist(char **path, t_data *data, char *cmd)
// {
// 	if (!ft_strchr(cmd, '/'))
// 		*path = find_cmd(data, cmd);
// 	else
// 	{
// 		*path = ft_strdup(cmd);
// 		if (!*path)
// 			return (false);
// 	}
// 	if (!(*path))
// 	{
// 		data->exit_code = 127;
// 		return (false);
// 	}
// 	if (access((*path), X_OK))
// 	{
// 		perror(*path);
// 		free(*path);
// 		*path = NULL;
// 		data->exit_code = 126;
// 		return (false);
// 	}
// 	if (!check_dir(path, cmd, data))
// 		return (false);
// 	return (true);
// }


// static void	redirect_in_out(t_data *data, t_cmd *cmd, int *pip)
// {
// 	(void)data;
// 	close(pip[0]);
// 	if (cmd->infile >= 0)
// 	{
// 		dup2(cmd->infile, 0);
// 		close(cmd->infile);
// 	}
// 	if (cmd->outfile >= 0)
// 	{
// 		dup2(cmd->outfile, 1);
// 		close(cmd->outfile);
// 	}
// 	else if (cmd->next)
// 		dup2(pip[1], 1);
// 	close(pip[1]);
// }



// void	child_process(t_data *data, t_cmd *cmd, int *pip)
// {
// 	char	*path;
// 	char	**env;

// 	path = NULL;
// 	setup_child_signals();
// 	if (cmd->skip_cmd)
// 		exit(1);
// 	else if (is_builtin(cmd->argv[0]))
// 	{
// 		launch_builtin(data, cmd);
// 		exit(data->exit_code);
// 	}
// 	else if (cmd_exist(&path, data, cmd->argv[0]))
// 	{
// 		redirect_in_out(data, cmd, pip);
// 		env = lst_to_arr(data->env);
// 		if (!env)
// 			exit(1);
// 		execve(path, cmd->argv, env);
// 		perror("minishell: execve");
// 		free_array(env);
// 	}
// 	if (path)
// 		free(path);
// 	exit(data->exit_code);
// }

static bool	cmd_exist(char **path, t_data *data, char *cmd)
{
	printf("DEBUG: cmd_exist called with cmd: %s\n", cmd);
	
	if (!ft_strchr(cmd, '/'))
		*path = find_cmd(data, cmd);
	else
	{
		*path = ft_strdup(cmd);
		if (!*path)
			return (false);
	}
	printf("DEBUG: cmd_exist - path found: %s\n", *path ? *path : "NULL");
	
	if (!(*path))
	{
		data->exit_code = 127;
		return (false);
	}
	if (access((*path), X_OK))
	{
		perror(*path);
		free(*path);
		*path = NULL;
		data->exit_code = 126;
		return (false);
	}
	printf("DEBUG: cmd_exist - access check passed\n");
	
	if (!check_dir(path, cmd, data))
		return (false);
	
	printf("DEBUG: cmd_exist returning true\n");
	return (true);
}

static void	redirect_in_out(t_data *data, t_cmd *cmd, int *pip)
{
	(void)data;
	printf("DEBUG: redirect_in_out started\n");
	printf("DEBUG: pip[0]=%d, pip[1]=%d\n", pip[0], pip[1]);
	close(pip[0]);
	
	// CHANGED: Only redirect if infile/outfile are actually set (not -1)
	if (cmd->infile >= 0)
	{
		printf("DEBUG: redirecting infile %d to stdin\n", cmd->infile);
		dup2(cmd->infile, 0);
		close(cmd->infile);
	}
	if (cmd->outfile >= 0)
	{
		printf("DEBUG: redirecting outfile %d to stdout\n", cmd->outfile);
		dup2(cmd->outfile, 1);
		close(cmd->outfile);
	}
	else if (cmd->next)
	{
		printf("DEBUG: redirecting pipe[1] to stdout\n");
		dup2(pip[1], 1);
	}
	close(pip[1]);
	printf("DEBUG: redirect_in_out completed\n");
}

void	child_process(t_data *data, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;
	int		j;

	printf("DEBUG: child_process started\n");
	printf("DEBUG: cmd->argv[0] = %s\n", cmd->argv[0] ? cmd->argv[0] : "NULL");
	
	path = NULL;
	setup_child_signals();
	if (cmd->skip_cmd)
		exit(1);
	else if (is_builtin(cmd->argv[0]))
	{
		launch_builtin(data, cmd);
		exit(data->exit_code);
	}
	else if (cmd_exist(&path, data, cmd->argv[0]))
	{
		printf("DEBUG: cmd_exist returned true, path = %s\n", path);
		redirect_in_out(data, cmd, pip);
		env = lst_to_arr(data->env);
		printf("DEBUG: env array created, first env: %s\n", env[0] ? env[0] : "NULL");
		
		// ADD ARGV DEBUG
		j = 0;
		while (cmd->argv[j])
		{
			printf("DEBUG: argv[%d] = %s\n", j, cmd->argv[j]);
			j++;
		}
		printf("DEBUG: argv[%d] = %s\n", j, cmd->argv[j] ? cmd->argv[j] : "NULL");
		
		printf("DEBUG: about to execve: %s\n", path);
		execve(path, cmd->argv, env);
		perror("minishell: execve");
		free_array(env);
	}
	if (path)
		free(path);
	exit(data->exit_code);
}