/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:33:37 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/14 12:45:27 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *read_full_line(void)
{
	char *line;
	char *next;
	char *tmp;

	line = readline("lolipop 🍭$ ");
	if (!line)
	{
		ft_putendl_fd("exit", 1);
		return (NULL);
	}
	while (has_unclosed_quote(line))
	{
		next = readline("> ");
		if (!next)
		{
			ft_putstr_fd("lolipop 🍭$ : unexpected EOF\n", 2);
			free(line);
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n");
		free(line);
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
	}
	return (line);
}
// This function reads a full line from the user, handling multi-line input if there are unclosed quotes.
