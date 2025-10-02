/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbugar <aalbugar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:33:37 by aalbugar          #+#    #+#             */
/*   Updated: 2025/10/02 17:50:03 by aalbugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_full_line(void)
{
	char	*line;
	char	*next;
	char	*tmp;

	line = readline("lolipop 🍭$ ");
	if (!line)
		return (NULL); // Ctrl-D at main prompt

	while (has_unclosed_quote(line))
	{
		next = readline("> ");
		if (!next) // Ctrl-D during continuation
		{
			ft_putstr_fd("lolipop 🍭$ : unexpected EOF while looking for matching quote\n", 2);
			free(line);
			return (NULL);
		}
		tmp = ft_strjoin(line, "\n"); // append next line
		free(line);
		line = ft_strjoin(tmp, next);
		free(tmp);
		free(next);
	}
	return (line);
}
