/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 12:20:20 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/23 12:47:07 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	parse_export_args(char *expanded, char **args)
// {
// 	char	*token;
// 	char	*arg_start;
// 	int		i;

// 	i = 1;
// 	args[0] = "export";
// 	token = expanded + 6;
// 	skip_spaces(&token);
// 	arg_start = token;
// 	while (*token)
// 	{
// 		if (*token == ' ')
// 		{
// 			args[i] = extract_arg(arg_start, token);
// 			if (args[i])
// 				i++;
// 			token++;
// 			skip_spaces(&token);
// 			arg_start = token;
// 		}
// 		else
// 			token++;
// 	}
// 	if (arg_start != token)
// 	{
// 		args[i] = extract_arg(arg_start, token);
// 		i++;
// 	}
// 	args[i] = NULL;
// }

void	parse_export_args(char *expanded, char **args)
{
	args[0] = "export";
	if (expanded[6])
	{
		args[1] = ft_strdup(expanded + 6);
		skip_spaces(&args[1]);
	}
	else
		args[1] = NULL;
	args[2] = NULL;
}

static void	cleanup_env(t_shell_state *state, t_env *env_list)
{
	char	**new_env;

	if (!env_list)
		return ;
	new_env = env_list_to_array(env_list);
	if (new_env)
	{
		free_str_array(state->env);
		state->env = new_env;
	}
	free_env_list(env_list);
}

int	handle_export(char *expanded, t_shell_state *state)
{
	char	*args[100];
	t_env	*env_list;
	int		result;

	parse_export_args(expanded, args);
	env_list = env_array_to_list(state->env);
	result = ft_export(args, &env_list);
	cleanup_env(state, env_list);
	free_str_array(args + 1);
	return (result);
}