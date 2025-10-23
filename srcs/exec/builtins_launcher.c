/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:22:39 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/22 14:22:42 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_echo(char *expanded)
{
	char	*args[100];
	char	*token;
	int		i;

	i = 0;
	args[i++] = "echo";
	token = expanded + 4;
	while (*token && *token == ' ')
		token++;
	if (*token)
	{
		args[i++] = token;
		while (*token)
		{
			if (*token == ' ')
			{
				*token = '\0';
				token++;
				while (*token && *token == ' ')
					token++;
				if (*token)
					args[i++] = token;
			}
			token++;
		}
	}
	args[i] = NULL;
	return (ft_echo(args));
}

static int	handle_unset(char *expanded, t_shell_state *state)
{
	char	*args[100];
	char	*token;
	int		i;

	i = 0;
	args[i++] = "unset";
	token = expanded + 5;
	while (*token && *token == ' ')
		token++;
	while (*token)
	{
		args[i] = token;
		while (*token && *token != ' ')
			token++;
		if (*token)
		{
			*token++ = '\0';
			while (*token && *token == ' ')
				token++;
		}
		i++;
	}
	args[i] = NULL;
	return (exec_unset(args, state));
}

static int	handle_exit(char *expanded, t_shell_state *state)
{
	char	*arg_start;
	char	*args[10];
	int		i;

	arg_start = expanded + 4;
	while (*arg_start == ' ')
		arg_start++;
	i = 0;
	args[i++] = "exit";
	if (*arg_start)
	{
		char *token = ft_strdup(arg_start);
		args[i++] = token;
		args[i] = NULL;
		exec_exit(args, state);
		free(token);
	}
	else
	{
		args[i] = NULL;
		exec_exit(args, state);
	}
	return (0);
}

static int	handle_cd(char *expanded, t_shell_state *state)
{
	char	*args[100];
	char	*token;
	int		i;

	i = 0;
	args[i++] = "cd";
	token = expanded + 2;
	while (*token && *token == ' ')
		token++;
	if (*token)
	{
		args[i++] = token;
		while (*token)
		{
			if (*token == ' ')
			{
				*token = '\0';
				token++;
				while (*token && *token == ' ')
					token++;
				if (*token)
					args[i++] = token;
			}
			token++;
		}
	}
	args[i] = NULL;
	return (ft_cd(args, &state->env));
}

static int	handle_export(char *expanded, t_shell_state *state)
{
	char	*args[100];
	char	*token;
	int		i;
	int		result;
	t_env	*env_list;

	i = 0;
	args[i++] = "export";
	token = expanded + 6;
	while (*token && *token == ' ')
		token++;
	if (*token)
	{
		args[i++] = token;
		while (*token)
		{
			if (*token == ' ')
			{
				*token = '\0';
				token++;
				while (*token && *token == ' ')
					token++;
				if (*token)
					args[i++] = token;
			}
			token++;
		}
	}
	args[i] = NULL;
	
	// Convert current env array to linked list for export
	env_list = env_array_to_list(state->env);
	result = ft_export(args, &env_list);
	
	// Convert back to array format for compatibility
	if (env_list)
	{
		char **new_env = env_list_to_array(env_list);
		if (new_env)
		{
			// Free old environment and replace with new one
			char **old_env = state->env;
			state->env = new_env;
			// Free old environment array
			if (old_env)
			{
				int j = 0;
				while (old_env[j])
					free(old_env[j++]);
				free(old_env);
			}
		}
		free_env_list(env_list);
	}
	
	return (result);
}

int	handle_builtins(char *expanded, t_shell_state *state)
{
	if (ft_strncmp(expanded, "echo", 4) == 0 && (expanded[4] == ' ' || expanded[4] == '\0'))
		return (handle_echo(expanded));
	else if (ft_strcmp(expanded, "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(expanded, "env") == 0)
		return (ft_env(state->env));
	else if (ft_strncmp(expanded, "unset", 5) == 0 && (expanded[5] == ' ' || expanded[5] == '\0'))
		return (handle_unset(expanded, state));
	else if (ft_strncmp(expanded, "exit", 4) == 0 && (expanded[4] == ' ' || expanded[4] == '\0'))
		return (handle_exit(expanded, state));
	else if (ft_strncmp(expanded, "cd", 2) == 0 && (expanded[2] == ' ' || expanded[2] == '\0'))
		return (handle_cd(expanded, state));
	else if (ft_strncmp(expanded, "export", 6) == 0 && (expanded[6] == ' ' || expanded[6] == '\0'))
		return (handle_export(expanded, state));
	
	return (-1); // Not a builtin command
}