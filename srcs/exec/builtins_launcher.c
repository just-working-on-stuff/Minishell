/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_launcher.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:22:39 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/27 17:43:40 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ---------- small helpers ---------- */

static int strings_equal(const char *a, const char *b)
{
	if (!a || !b)
		return (0);
	return (ft_strcmp(a, b) == 0);
}
// clear_builtin
int	clear_builtin(t_cmd *cmd)
{
	(void)cmd;
	write(1, "\033[2J\033[H", 7);
	return (0);
}
/* ---------- thin wrappers over your existing builtins ---------- */

static int builtin_echo(t_cmd *command)
{
	return (ft_echo(command->argv));
}

static int builtin_cd(t_data *shell, t_cmd *command)
{
	return (ft_cd(shell, command->argv));
}

static int builtin_pwd(void)
{
	return (ft_pwd());
}

static int builtin_export(t_data *shell, t_cmd *command)
{
	return (ft_export(command->argv, &shell->env));
}

static int builtin_unset(t_data *shell, t_cmd *command)
{
	return (ft_unset(command->argv, &shell->env));
}

static int builtin_env(t_data *shell)
{
	return (ft_env(shell->env));
}

/* ---------- core dispatcher: mirrors the "first" style ---------- */
static void	handle_exit_redirection(int stdout_backup, t_data *shell, t_cmd *command)
{
	if (command->outfile >= 0)
	{
		dup2(stdout_backup, 1);
		close(stdout_backup);
	}
	ft_exit(shell, command->argv);
}

static void exec_builtin_dispatch(int stdout_backup, t_data *shell, t_cmd *command)
{
	char *command_name;
	
	command_name = command->argv[0];
	if (strings_equal(command_name, "echo"))
		shell->exit_code = builtin_echo(command);
	else if (strings_equal(command_name, "cd"))
		shell->exit_code = builtin_cd(shell, command);
	else if (strings_equal(command_name, "pwd"))
		shell->exit_code = builtin_pwd();
	else if (strings_equal(command_name, "export"))
		shell->exit_code = builtin_export(shell, command);
	else if (strings_equal(command_name, "unset"))
		shell->exit_code = builtin_unset(shell, command);
	else if (strings_equal(command_name, "env"))
		shell->exit_code = builtin_env(shell);
	else if (strings_equal(command_name, "clear"))
		shell->exit_code = builtin_clear();
	else if (strings_equal(command_name, "exit"))
		handle_exit_redirection(stdout_backup, shell, command);
}
/* ---------- public entry: handles stdout redirection safely ---------- */

bool launch_builtin(t_data *shell, t_cmd *command)
{
	int stdout_backup;

	stdout_backup = -1;
	if (command->outfile >= 0)
	{
		stdout_backup = dup(1);
		if (stdout_backup < 0 || dup2(command->outfile, 1) < 0)
		{
			if (stdout_backup >= 0)
				close(stdout_backup);
			shell->exit_code = 1;
			return (true);
		}
	}
	exec_builtin_dispatch(stdout_backup, shell, command);
	if (command->outfile >= 0)
	{
		dup2(stdout_backup, 1);
		close(stdout_backup);
	}
	return (true);
}