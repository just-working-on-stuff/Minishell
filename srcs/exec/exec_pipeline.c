/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 20:00:00 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/27 20:00:00 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (!ft_strcmp("echo", cmd) || !ft_strcmp("cd", cmd) \
		|| !ft_strcmp("pwd", cmd) || !ft_strcmp("export", cmd) \
		|| !ft_strcmp("unset", cmd) || !ft_strcmp("env", cmd) \
		|| !ft_strcmp("exit", cmd) || !ft_strcmp("clear", cmd))
		return (true);
	return (false);
}

static void	parent_process(t_data *data, t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->infile >= 0)
		close(cmd->infile);
	if (cmd->next && cmd->next->infile == -1)
		cmd->next->infile = pip[0];
	else
		close(pip[0]);
}

static bool	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("minishell: fork");
		return (false);
	}
	else if (pid == 0)
	{
		child_process(data, cmd, pip);
		exit(data->exit_code);
	}
	else
	{
		parent_process(data, cmd, pip);
		return (true);
	}
}

static void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	t_cmd	*tmp;

	tmp = data->cmds;
	while (tmp)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->exit_code = 128 + WTERMSIG(status);
		if (tmp->outfile >= 0)
			close(tmp->outfile);
		if (tmp->infile >= 0)
			close(tmp->infile);
		tmp = tmp->next;
	}
}

bool	exec_pipeline(t_data *data)
{
	t_cmd	*tmp;
	int		pip[2];

	if (!data->cmds)
		return (true);
	if (data->cmds && !data->cmds->next && data->cmds->argv[0] \
		&& is_builtin(data->cmds->argv[0]))
		return (launch_builtin(data, data->cmds));
	tmp = data->cmds;
	while (tmp)
	{
		if (pipe(pip) == -1)
		{
			perror("minishell: pipe");
			return (false);
		}
		if (!exec_cmd(data, tmp, pip))
			return (false);
		tmp = tmp->next;
	}
	wait_all(data);
	return (true);
}