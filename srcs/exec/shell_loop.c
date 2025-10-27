/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghsaad <ghsaad@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:13:50 by ghsaad            #+#    #+#             */
/*   Updated: 2025/10/27 14:14:09 by ghsaad           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	shell_step(t_data *data)
{
	char	*line;

	line = read_full_line();
	if (!line)
		return (0);
	if (*line)
	{
		add_history(line);
		if (shell_parse_line(data, line))
			(void)shell_exec(data);
	}
	free(line);
	free_cmds(data->cmds);
	free_token(&data->token);
	return (1);
}

void	shell_teardown(t_data *data)
{
	rl_clear_history();
	free_cmds(data->cmds);
	free_token(&data->token);
	free_list(&data->env);
	shell_cleanup(data);
}